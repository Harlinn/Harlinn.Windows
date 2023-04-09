/*
 * Copyright 2015-2021 Arm Limited
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * At your option, you may choose to accept this material under either:
 *  1. The Apache License, Version 2.0, found at <http://www.apache.org/licenses/LICENSE-2.0>, or
 *  2. The MIT License, found at <http://opensource.org/licenses/MIT>.
 */

#ifndef SPIRV_CROSS_GLSL_HPP
#define SPIRV_CROSS_GLSL_HPP

#include "GLSL.std.450.h"
#include "spirv_cross.hpp"
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace SPIRV_CROSS_NAMESPACE
{
enum PlsFormat
{
	PlsNone = 0,

	PlsR11FG11FB10F,
	PlsR32F,
	PlsRG16F,
	PlsRGB10A2,
	PlsRGBA8,
	PlsRG16,

	PlsRGBA8I,
	PlsRG16I,

	PlsRGB10A2UI,
	PlsRGBA8UI,
	PlsRG16UI,
	PlsR32UI
};

struct PlsRemap
{
	uint32_t id;
	PlsFormat format;
};

enum AccessChainFlagBits
{
	ACCESS_CHAIN_INDEX_IS_LITERAL_BIT = 1 << 0,
	ACCESS_CHAIN_CHAIN_ONLY_BIT = 1 << 1,
	ACCESS_CHAIN_PTR_CHAIN_BIT = 1 << 2,
	ACCESS_CHAIN_SKIP_REGISTER_EXPRESSION_READ_BIT = 1 << 3,
	ACCESS_CHAIN_LITERAL_MSB_FORCE_ID = 1 << 4,
	ACCESS_CHAIN_FLATTEN_ALL_MEMBERS_BIT = 1 << 5,
	ACCESS_CHAIN_FORCE_COMPOSITE_BIT = 1 << 6
};
typedef uint32_t AccessChainFlags;

class CompilerGLSL : public Compiler
{
public:
	struct Options
	{
		// The shading language version. Corresponds to #version $VALUE.
		uint32_t version = 450;

		// Emit the OpenGL ES shading language instead of desktop OpenGL.
		bool es = false;

		// Debug option to always emit temporary variables for all expressions.
		bool force_temporary = false;

		// If true, Vulkan GLSL features are used instead of GL-compatible features.
		// Mostly useful for debugging SPIR-V files.
		bool vulkan_semantics = false;

		// If true, gl_PerVertex is explicitly redeclared in vertex, geometry and tessellation shaders.
		// The members of gl_PerVertex is determined by which built-ins are declared by the shader.
		// This option is ignored in ES versions, as redeclaration in ES is not required, and it depends on a different extension
		// (EXT_shader_io_blocks) which makes things a bit more fuzzy.
		bool separate_shader_objects = false;

		// Flattens multidimensional arrays, e.g. float foo[a][b][c] into single-dimensional arrays,
		// e.g. float foo[a * b * c].
		// This function does not change the actual SPIRType of any object.
		// Only the generated code, including declarations of interface variables are changed to be single array dimension.
		bool flatten_multidimensional_arrays = false;

		// For older desktop GLSL targets than version 420, the
		// GL_ARB_shading_language_420pack extensions is used to be able to support
		// layout(binding) on UBOs and samplers.
		// If disabled on older targets, binding decorations will be stripped.
		bool enable_420pack_extension = true;

		// In non-Vulkan GLSL, emit push constant blocks as UBOs rather than plain uniforms.
		bool emit_push_constant_as_uniform_buffer = false;

		// Always emit uniform blocks as plain uniforms, regardless of the GLSL version, even when UBOs are supported.
		// Does not apply to shader storage or push constant blocks.
		bool emit_uniform_buffer_as_plain_uniforms = false;

		// Emit OpLine directives if present in the module.
		// May not correspond exactly to original source, but should be a good approximation.
		bool emit_line_directives = false;

		// In cases where readonly/writeonly decoration are not used at all,
		// we try to deduce which qualifier(s) we should actually used, since actually emitting
		// read-write decoration is very rare, and older glslang/HLSL compilers tend to just emit readwrite as a matter of fact.
		// The default (true) is to enable automatic deduction for these cases, but if you trust the decorations set
		// by the SPIR-V, it's recommended to set this to false.
		bool enable_storage_image_qualifier_deduction = true;

		// On some targets (WebGPU), uninitialized variables are banned.
		// If this is enabled, all variables (temporaries, Private, Function)
		// which would otherwise be uninitialized will now be initialized to 0 instead.
		bool force_zero_initialized_variables = false;

		// In GLSL, force use of I/O block flattening, similar to
		// what happens on legacy GLSL targets for blocks and structs.
		bool force_flattened_io_blocks = false;

		// If non-zero, controls layout(num_views = N) in; in GL_OVR_multiview2.
		uint32_t ovr_multiview_view_count = 0;

		enum Precision
		{
			DontCare,
			Lowp,
			Mediump,
			Highp
		};

		struct VertexOptions
		{
			// "Vertex-like shader" here is any shader stage that can write BuiltInPosition.

			// GLSL: In vertex-like shaders, rewrite [0, w] depth (Vulkan/D3D style) to [-w, w] depth (GL style).
			// MSL: In vertex-like shaders, rewrite [-w, w] depth (GL style) to [0, w] depth.
			// HLSL: In vertex-like shaders, rewrite [-w, w] depth (GL style) to [0, w] depth.
			bool fixup_clipspace = false;

			// In vertex-like shaders, inverts gl_Position.y or equivalent.
			bool flip_vert_y = false;

			// GLSL only, for HLSL version of this option, see CompilerHLSL.
			// If true, the backend will assume that InstanceIndex will need to apply
			// a base instance offset. Set to false if you know you will never use base instance
			// functionality as it might remove some internal uniforms.
			bool support_nonzero_base_instance = true;
		} vertex;

		struct FragmentOptions
		{
			// Add precision mediump float in ES targets when emitting GLES source.
			// Add precision highp int in ES targets when emitting GLES source.
			Precision default_float_precision = Mediump;
			Precision default_int_precision = Highp;
		} fragment;
	};

	void remap_pixel_local_storage(std::vector<PlsRemap> inputs, std::vector<PlsRemap> outputs)
	{
		pls_inputs = std::move(inputs);
		pls_outputs = std::move(outputs);
		remap_pls_variables();
	}

	// Redirect a subpassInput reading from input_attachment_index to instead load its value from
	// the color attachment at location = color_location. Requires ESSL.
	// If coherent, uses GL_EXT_shader_framebuffer_fetch, if not, uses noncoherent variant.
	SPVC_EXPORT void remap_ext_framebuffer_fetch(uint32_t input_attachment_index, uint32_t color_location, bool coherent);

	explicit CompilerGLSL(std::vector<uint32_t> spirv_)
	    : Compiler(std::move(spirv_))
	{
		init();
	}

	CompilerGLSL(const uint32_t *ir_, size_t word_count)
	    : Compiler(ir_, word_count)
	{
		init();
	}

	explicit CompilerGLSL(const ParsedIR &ir_)
	    : Compiler(ir_)
	{
		init();
	}

	explicit CompilerGLSL(ParsedIR &&ir_)
	    : Compiler(std::move(ir_))
	{
		init();
	}

	const Options &get_common_options() const
	{
		return options;
	}

	void set_common_options(const Options &opts)
	{
		options = opts;
	}

	SPVC_EXPORT std::string compile() override;

	// Returns the current string held in the conversion buffer. Useful for
	// capturing what has been converted so far when compile() throws an error.
	SPVC_EXPORT std::string get_partial_source();

	// Adds a line to be added right after #version in GLSL backend.
	// This is useful for enabling custom extensions which are outside the scope of SPIRV-Cross.
	// This can be combined with variable remapping.
	// A new-line will be added.
	//
	// While add_header_line() is a more generic way of adding arbitrary text to the header
	// of a GLSL file, require_extension() should be used when adding extensions since it will
	// avoid creating collisions with SPIRV-Cross generated extensions.
	//
	// Code added via add_header_line() is typically backend-specific.
	SPVC_EXPORT void add_header_line(const std::string &str);

	// Adds an extension which is required to run this shader, e.g.
	// require_extension("GL_KHR_my_extension");
	SPVC_EXPORT void require_extension(const std::string &ext);

	// Legacy GLSL compatibility method.
	// Takes a uniform or push constant variable and flattens it into a (i|u)vec4 array[N]; array instead.
	// For this to work, all types in the block must be the same basic type, e.g. mixing vec2 and vec4 is fine, but
	// mixing int and float is not.
	// The name of the uniform array will be the same as the interface block name.
	SPVC_EXPORT void flatten_buffer_block(VariableID id);

	// After compilation, query if a variable ID was used as a depth resource.
	// This is meaningful for MSL since descriptor types depend on this knowledge.
	// Cases which return true:
	// - Images which are declared with depth = 1 image type.
	// - Samplers which are statically used at least once with Dref opcodes.
	// - Images which are statically used at least once with Dref opcodes.
	SPVC_EXPORT bool variable_is_depth_or_compare(VariableID id) const;

	// If a shader output is active in this stage, but inactive in a subsequent stage,
	// this can be signalled here. This can be used to work around certain cross-stage matching problems
	// which plagues MSL and HLSL in certain scenarios.
	// An output which matches one of these will not be emitted in stage output interfaces, but rather treated as a private
	// variable.
	// This option is only meaningful for MSL and HLSL, since GLSL matches by location directly.
	// Masking builtins only takes effect if the builtin in question is part of the stage output interface.
	SPVC_EXPORT void mask_stage_output_by_location(uint32_t location, uint32_t component);
	SPVC_EXPORT void mask_stage_output_by_builtin(spv::BuiltIn builtin);

protected:
	struct ShaderSubgroupSupportHelper
	{
		// lower enum value = greater priority
		enum Candidate
		{
			KHR_shader_subgroup_ballot,
			KHR_shader_subgroup_basic,
			KHR_shader_subgroup_vote,
			NV_gpu_shader_5,
			NV_shader_thread_group,
			NV_shader_thread_shuffle,
			ARB_shader_ballot,
			ARB_shader_group_vote,
			AMD_gcn_shader,

			CandidateCount
		};

		SPVC_EXPORT static const char *get_extension_name(Candidate c);
		SPVC_EXPORT static SmallVector<std::string> get_extra_required_extension_names(Candidate c);
		SPVC_EXPORT static const char *get_extra_required_extension_predicate(Candidate c);

		enum Feature
		{
			SubgroupMask = 0,
			SubgroupSize = 1,
			SubgroupInvocationID = 2,
			SubgroupID = 3,
			NumSubgroups = 4,
			SubgroupBroadcast_First = 5,
			SubgroupBallotFindLSB_MSB = 6,
			SubgroupAll_Any_AllEqualBool = 7,
			SubgroupAllEqualT = 8,
			SubgroupElect = 9,
			SubgroupBarrier = 10,
			SubgroupMemBarrier = 11,
			SubgroupBallot = 12,
			SubgroupInverseBallot_InclBitCount_ExclBitCout = 13,
			SubgroupBallotBitExtract = 14,
			SubgroupBallotBitCount = 15,

			FeatureCount
		};

		using FeatureMask = uint32_t;
		static_assert(sizeof(FeatureMask) * 8u >= FeatureCount, "Mask type needs more bits.");

		using CandidateVector = SmallVector<Candidate, CandidateCount>;
		using FeatureVector = SmallVector<Feature>;

		SPVC_EXPORT static FeatureVector get_feature_dependencies(Feature feature);
		SPVC_EXPORT static FeatureMask get_feature_dependency_mask(Feature feature);
		SPVC_EXPORT static bool can_feature_be_implemented_without_extensions(Feature feature);
		SPVC_EXPORT static Candidate get_KHR_extension_for_feature(Feature feature);

		struct Result
		{
			Result();
			uint32_t weights[CandidateCount];
		};

		SPVC_EXPORT void request_feature(Feature feature);
		SPVC_EXPORT bool is_feature_requested(Feature feature) const;
		SPVC_EXPORT Result resolve() const;

		SPVC_EXPORT static CandidateVector get_candidates_for_feature(Feature ft, const Result &r);

	private:
		SPVC_EXPORT static CandidateVector get_candidates_for_feature(Feature ft);
		SPVC_EXPORT static FeatureMask build_mask(const SmallVector<Feature> &features);
		FeatureMask feature_mask = 0;
	};

	// TODO remove this function when all subgroup ops are supported (or make it always return true)
	SPVC_EXPORT static bool is_supported_subgroup_op_in_opengl(spv::Op op);

	SPVC_EXPORT void reset();
	SPVC_EXPORT void emit_function(SPIRFunction &func, const Bitset &return_flags);

	SPVC_EXPORT bool has_extension(const std::string &ext) const;
	SPVC_EXPORT void require_extension_internal(const std::string &ext);

	// Virtualize methods which need to be overridden by subclass targets like C++ and such.
	SPVC_EXPORT virtual void emit_function_prototype(SPIRFunction &func, const Bitset &return_flags);

	SPIRBlock *current_emitting_block = nullptr;
	SPIRBlock *current_emitting_switch = nullptr;
	bool current_emitting_switch_fallthrough = false;

	SPVC_EXPORT virtual void emit_instruction(const Instruction &instr);
	SPVC_EXPORT void emit_block_instructions(SPIRBlock &block);
	SPVC_EXPORT virtual void emit_glsl_op(uint32_t result_type, uint32_t result_id, uint32_t op, const uint32_t *args,
	                          uint32_t count);
	SPVC_EXPORT virtual void emit_spv_amd_shader_ballot_op(uint32_t result_type, uint32_t result_id, uint32_t op,
	                                           const uint32_t *args, uint32_t count);
	SPVC_EXPORT virtual void emit_spv_amd_shader_explicit_vertex_parameter_op(uint32_t result_type, uint32_t result_id, uint32_t op,
	                                                              const uint32_t *args, uint32_t count);
	SPVC_EXPORT virtual void emit_spv_amd_shader_trinary_minmax_op(uint32_t result_type, uint32_t result_id, uint32_t op,
	                                                   const uint32_t *args, uint32_t count);
	SPVC_EXPORT virtual void emit_spv_amd_gcn_shader_op(uint32_t result_type, uint32_t result_id, uint32_t op, const uint32_t *args,
	                                        uint32_t count);
	SPVC_EXPORT virtual void emit_header();
	SPVC_EXPORT void emit_line_directive(uint32_t file_id, uint32_t line_literal);
	SPVC_EXPORT void build_workgroup_size(SmallVector<std::string> &arguments, const SpecializationConstant &x,
	                          const SpecializationConstant &y, const SpecializationConstant &z);

	SPVC_EXPORT void request_subgroup_feature(ShaderSubgroupSupportHelper::Feature feature);

	SPVC_EXPORT virtual void emit_sampled_image_op(uint32_t result_type, uint32_t result_id, uint32_t image_id, uint32_t samp_id);
	SPVC_EXPORT virtual void emit_texture_op(const Instruction &i, bool sparse);
	SPVC_EXPORT virtual std::string to_texture_op(const Instruction &i, bool sparse, bool *forward,
	                                  SmallVector<uint32_t> &inherited_expressions);
	SPVC_EXPORT virtual void emit_subgroup_op(const Instruction &i);
	SPVC_EXPORT virtual std::string type_to_glsl(const SPIRType &type, uint32_t id = 0);
	SPVC_EXPORT virtual std::string builtin_to_glsl(spv::BuiltIn builtin, spv::StorageClass storage);
	SPVC_EXPORT virtual void emit_struct_member(const SPIRType &type, uint32_t member_type_id, uint32_t index,
	                                const std::string &qualifier = "", uint32_t base_offset = 0);
	SPVC_EXPORT virtual void emit_struct_padding_target(const SPIRType &type);
	SPVC_EXPORT virtual std::string image_type_glsl(const SPIRType &type, uint32_t id = 0);
	SPVC_EXPORT std::string constant_expression(const SPIRConstant &c);
	SPVC_EXPORT std::string constant_op_expression(const SPIRConstantOp &cop);
	SPVC_EXPORT virtual std::string constant_expression_vector(const SPIRConstant &c, uint32_t vector);
	SPVC_EXPORT virtual void emit_fixup();
	SPVC_EXPORT virtual std::string variable_decl(const SPIRType &type, const std::string &name, uint32_t id = 0);
	SPVC_EXPORT virtual bool variable_decl_is_remapped_storage(const SPIRVariable &var, spv::StorageClass storage) const;
	SPVC_EXPORT virtual std::string to_func_call_arg(const SPIRFunction::Parameter &arg, uint32_t id);

	struct TextureFunctionBaseArguments
	{
		// GCC 4.8 workarounds, it doesn't understand '{}' constructor here, use explicit default constructor.
		TextureFunctionBaseArguments() = default;
		VariableID img = 0;
		const SPIRType *imgtype = nullptr;
		bool is_fetch = false, is_gather = false, is_proj = false;
	};

	struct TextureFunctionNameArguments
	{
		// GCC 4.8 workarounds, it doesn't understand '{}' constructor here, use explicit default constructor.
		TextureFunctionNameArguments() = default;
		TextureFunctionBaseArguments base;
		bool has_array_offsets = false, has_offset = false, has_grad = false;
		bool has_dref = false, is_sparse_feedback = false, has_min_lod = false;
		uint32_t lod = 0;
	};
	SPVC_EXPORT virtual std::string to_function_name(const TextureFunctionNameArguments &args);

	struct TextureFunctionArguments
	{
		// GCC 4.8 workarounds, it doesn't understand '{}' constructor here, use explicit default constructor.
		TextureFunctionArguments() = default;
		TextureFunctionBaseArguments base;
		uint32_t coord = 0, coord_components = 0, dref = 0;
		uint32_t grad_x = 0, grad_y = 0, lod = 0, coffset = 0, offset = 0;
		uint32_t bias = 0, component = 0, sample = 0, sparse_texel = 0, min_lod = 0;
		bool nonuniform_expression = false;
	};
	SPVC_EXPORT virtual std::string to_function_args(const TextureFunctionArguments &args, bool *p_forward);

	SPVC_EXPORT void emit_sparse_feedback_temporaries(uint32_t result_type_id, uint32_t id, uint32_t &feedback_id,
	                                      uint32_t &texel_id);
	SPVC_EXPORT uint32_t get_sparse_feedback_texel_id(uint32_t id) const;
	SPVC_EXPORT virtual void emit_buffer_block(const SPIRVariable &type);
	SPVC_EXPORT virtual void emit_push_constant_block(const SPIRVariable &var);
	SPVC_EXPORT virtual void emit_uniform(const SPIRVariable &var);
	SPVC_EXPORT virtual std::string unpack_expression_type(std::string expr_str, const SPIRType &type, uint32_t physical_type_id,
	                                           bool packed_type, bool row_major);

	SPVC_EXPORT virtual bool builtin_translates_to_nonarray(spv::BuiltIn builtin) const;

	SPVC_EXPORT void emit_copy_logical_type(uint32_t lhs_id, uint32_t lhs_type_id, uint32_t rhs_id, uint32_t rhs_type_id,
	                            SmallVector<uint32_t> chain);

	StringStream<> buffer;

	template <typename T>
	inline void statement_inner(T &&t)
	{
		buffer << std::forward<T>(t);
		statement_count++;
	}

	template <typename T, typename... Ts>
	inline void statement_inner(T &&t, Ts &&... ts)
	{
		buffer << std::forward<T>(t);
		statement_count++;
		statement_inner(std::forward<Ts>(ts)...);
	}

	template <typename... Ts>
	inline void statement(Ts &&... ts)
	{
		if (is_forcing_recompilation())
		{
			// Do not bother emitting code while force_recompile is active.
			// We will compile again.
			statement_count++;
			return;
		}

		if (redirect_statement)
		{
			redirect_statement->push_back(join(std::forward<Ts>(ts)...));
			statement_count++;
		}
		else
		{
			for (uint32_t i = 0; i < indent; i++)
				buffer << "    ";
			statement_inner(std::forward<Ts>(ts)...);
			buffer << '\n';
		}
	}

	template <typename... Ts>
	inline void statement_no_indent(Ts &&... ts)
	{
		auto old_indent = indent;
		indent = 0;
		statement(std::forward<Ts>(ts)...);
		indent = old_indent;
	}

	// Used for implementing continue blocks where
	// we want to obtain a list of statements we can merge
	// on a single line separated by comma.
	SmallVector<std::string> *redirect_statement = nullptr;
	const SPIRBlock *current_continue_block = nullptr;

	SPVC_EXPORT void begin_scope();
	SPVC_EXPORT void end_scope();
	SPVC_EXPORT void end_scope(const std::string &trailer);
	SPVC_EXPORT void end_scope_decl();
	SPVC_EXPORT void end_scope_decl(const std::string &decl);

	Options options;

	SPVC_EXPORT virtual std::string type_to_array_glsl(
	    const SPIRType &type); // Allow Metal to use the array<T> template to make arrays a value type
	SPVC_EXPORT std::string to_array_size(const SPIRType &type, uint32_t index);
	SPVC_EXPORT uint32_t to_array_size_literal(const SPIRType &type, uint32_t index) const;
	SPVC_EXPORT uint32_t to_array_size_literal(const SPIRType &type) const;
	SPVC_EXPORT virtual std::string variable_decl(const SPIRVariable &variable); // Threadgroup arrays can't have a wrapper type
	SPVC_EXPORT std::string variable_decl_function_local(SPIRVariable &variable);

	SPVC_EXPORT void add_local_variable_name(uint32_t id);
	SPVC_EXPORT void add_resource_name(uint32_t id);
	SPVC_EXPORT void add_member_name(SPIRType &type, uint32_t name);
	SPVC_EXPORT void add_function_overload(const SPIRFunction &func);

	SPVC_EXPORT virtual bool is_non_native_row_major_matrix(uint32_t id);
	SPVC_EXPORT virtual bool member_is_non_native_row_major_matrix(const SPIRType &type, uint32_t index);
	SPVC_EXPORT bool member_is_remapped_physical_type(const SPIRType &type, uint32_t index) const;
	SPVC_EXPORT bool member_is_packed_physical_type(const SPIRType &type, uint32_t index) const;
	SPVC_EXPORT virtual std::string convert_row_major_matrix(std::string exp_str, const SPIRType &exp_type,
	                                             uint32_t physical_type_id, bool is_packed);

	std::unordered_set<std::string> local_variable_names;
	std::unordered_set<std::string> resource_names;
	std::unordered_set<std::string> block_input_names;
	std::unordered_set<std::string> block_output_names;
	std::unordered_set<std::string> block_ubo_names;
	std::unordered_set<std::string> block_ssbo_names;
	std::unordered_set<std::string> block_names; // A union of all block_*_names.
	std::unordered_map<std::string, std::unordered_set<uint64_t>> function_overloads;
	std::unordered_map<uint32_t, std::string> preserved_aliases;
	SPVC_EXPORT void preserve_alias_on_reset(uint32_t id);
	SPVC_EXPORT void reset_name_caches();

	bool processing_entry_point = false;

	// Can be overriden by subclass backends for trivial things which
	// shouldn't need polymorphism.
	struct BackendVariations
	{
		std::string discard_literal = "discard";
		std::string demote_literal = "demote";
		std::string null_pointer_literal = "";
		bool float_literal_suffix = false;
		bool double_literal_suffix = true;
		bool uint32_t_literal_suffix = true;
		bool long_long_literal_suffix = false;
		const char *basic_int_type = "int";
		const char *basic_uint_type = "uint";
		const char *basic_int8_type = "int8_t";
		const char *basic_uint8_type = "uint8_t";
		const char *basic_int16_type = "int16_t";
		const char *basic_uint16_type = "uint16_t";
		const char *int16_t_literal_suffix = "s";
		const char *uint16_t_literal_suffix = "us";
		const char *nonuniform_qualifier = "nonuniformEXT";
		const char *boolean_mix_function = "mix";
		bool swizzle_is_function = false;
		bool shared_is_implied = false;
		bool unsized_array_supported = true;
		bool explicit_struct_type = false;
		bool use_initializer_list = false;
		bool use_typed_initializer_list = false;
		bool can_declare_struct_inline = true;
		bool can_declare_arrays_inline = true;
		bool native_row_major_matrix = true;
		bool use_constructor_splatting = true;
		bool allow_precision_qualifiers = false;
		bool can_swizzle_scalar = false;
		bool force_gl_in_out_block = false;
		bool can_return_array = true;
		bool allow_truncated_access_chain = false;
		bool supports_extensions = false;
		bool supports_empty_struct = false;
		bool array_is_value_type = true;
		bool buffer_offset_array_is_value_type = true;
		bool comparison_image_samples_scalar = false;
		bool native_pointers = false;
		bool support_small_type_sampling_result = false;
		bool support_case_fallthrough = true;
		bool use_array_constructor = false;
		bool needs_row_major_load_workaround = false;
		bool support_pointer_to_pointer = false;
		bool support_precise_qualifier = false;
	} backend;

	SPVC_EXPORT void emit_struct(SPIRType &type);
	SPVC_EXPORT void emit_resources();
	SPVC_EXPORT void emit_extension_workarounds(spv::ExecutionModel model);
	SPVC_EXPORT void emit_buffer_block_native(const SPIRVariable &var);
	SPVC_EXPORT void emit_buffer_reference_block(SPIRType &type, bool forward_declaration);
	SPVC_EXPORT void emit_buffer_block_legacy(const SPIRVariable &var);
	SPVC_EXPORT void emit_buffer_block_flattened(const SPIRVariable &type);
	SPVC_EXPORT void fixup_implicit_builtin_block_names();
	SPVC_EXPORT void emit_declared_builtin_block(spv::StorageClass storage, spv::ExecutionModel model);
	SPVC_EXPORT bool should_force_emit_builtin_block(spv::StorageClass storage);
	SPVC_EXPORT void emit_push_constant_block_vulkan(const SPIRVariable &var);
	SPVC_EXPORT void emit_push_constant_block_glsl(const SPIRVariable &var);
	SPVC_EXPORT void emit_interface_block(const SPIRVariable &type);
	SPVC_EXPORT void emit_flattened_io_block(const SPIRVariable &var, const char *qual);
	SPVC_EXPORT void emit_flattened_io_block_struct(const std::string &basename, const SPIRType &type, const char *qual,
	                                    const SmallVector<uint32_t> &indices);
	SPVC_EXPORT void emit_flattened_io_block_member(const std::string &basename, const SPIRType &type, const char *qual,
	                                    const SmallVector<uint32_t> &indices);
	SPVC_EXPORT void emit_block_chain(SPIRBlock &block);
	SPVC_EXPORT void emit_hoisted_temporaries(SmallVector<std::pair<TypeID, ID>> &temporaries);
	SPVC_EXPORT std::string constant_value_macro_name(uint32_t id);
	SPVC_EXPORT void emit_constant(const SPIRConstant &constant);
	SPVC_EXPORT void emit_specialization_constant_op(const SPIRConstantOp &constant);
	SPVC_EXPORT std::string emit_continue_block(uint32_t continue_block, bool follow_true_block, bool follow_false_block);
	SPVC_EXPORT bool attempt_emit_loop_header(SPIRBlock &block, SPIRBlock::Method method);

	SPVC_EXPORT void branch(BlockID from, BlockID to);
	SPVC_EXPORT void branch_to_continue(BlockID from, BlockID to);
	SPVC_EXPORT void branch(BlockID from, uint32_t cond, BlockID true_block, BlockID false_block);
	SPVC_EXPORT void flush_phi(BlockID from, BlockID to);
	SPVC_EXPORT void flush_variable_declaration(uint32_t id);
	SPVC_EXPORT void flush_undeclared_variables(SPIRBlock &block);
	SPVC_EXPORT void emit_variable_temporary_copies(const SPIRVariable &var);

	SPVC_EXPORT bool should_dereference(uint32_t id);
	SPVC_EXPORT bool should_forward(uint32_t id) const;
	SPVC_EXPORT bool should_suppress_usage_tracking(uint32_t id) const;
	SPVC_EXPORT void emit_mix_op(uint32_t result_type, uint32_t id, uint32_t left, uint32_t right, uint32_t lerp);
	SPVC_EXPORT void emit_nminmax_op(uint32_t result_type, uint32_t id, uint32_t op0, uint32_t op1, GLSLstd450 op);
	SPVC_EXPORT bool to_trivial_mix_op(const SPIRType &type, std::string &op, uint32_t left, uint32_t right, uint32_t lerp);
	SPVC_EXPORT void emit_quaternary_func_op(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, uint32_t op2,
	                             uint32_t op3, const char *op);
	SPVC_EXPORT void emit_trinary_func_op(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, uint32_t op2,
	                          const char *op);
	SPVC_EXPORT void emit_binary_func_op(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, const char *op);
	SPVC_EXPORT void emit_atomic_func_op(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, const char *op);
	SPVC_EXPORT void emit_atomic_func_op(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, uint32_t op2, const char *op);

	SPVC_EXPORT void emit_unary_func_op_cast(uint32_t result_type, uint32_t result_id, uint32_t op0, const char *op,
	                             SPIRType::BaseType input_type, SPIRType::BaseType expected_result_type);
	SPVC_EXPORT void emit_binary_func_op_cast(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, const char *op,
	                              SPIRType::BaseType input_type, bool skip_cast_if_equal_type);
	SPVC_EXPORT void emit_binary_func_op_cast_clustered(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1,
	                                        const char *op, SPIRType::BaseType input_type);
	SPVC_EXPORT void emit_trinary_func_op_cast(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, uint32_t op2,
	                               const char *op, SPIRType::BaseType input_type);
	SPVC_EXPORT void emit_trinary_func_op_bitextract(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1,
	                                     uint32_t op2, const char *op, SPIRType::BaseType expected_result_type,
	                                     SPIRType::BaseType input_type0, SPIRType::BaseType input_type1,
	                                     SPIRType::BaseType input_type2);
	SPVC_EXPORT void emit_bitfield_insert_op(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, uint32_t op2,
	                             uint32_t op3, const char *op, SPIRType::BaseType offset_count_type);

	SPVC_EXPORT void emit_unary_func_op(uint32_t result_type, uint32_t result_id, uint32_t op0, const char *op);
	SPVC_EXPORT void emit_unrolled_unary_op(uint32_t result_type, uint32_t result_id, uint32_t operand, const char *op);
	SPVC_EXPORT void emit_binary_op(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, const char *op);
	SPVC_EXPORT void emit_unrolled_binary_op(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, const char *op,
	                             bool negate, SPIRType::BaseType expected_type);
	SPVC_EXPORT void emit_binary_op_cast(uint32_t result_type, uint32_t result_id, uint32_t op0, uint32_t op1, const char *op,
	                         SPIRType::BaseType input_type, bool skip_cast_if_equal_type);

	SPVC_EXPORT SPIRType binary_op_bitcast_helper(std::string &cast_op0, std::string &cast_op1, SPIRType::BaseType &input_type,
	                                  uint32_t op0, uint32_t op1, bool skip_cast_if_equal_type);

	SPVC_EXPORT virtual bool emit_complex_bitcast(uint32_t result_type, uint32_t id, uint32_t op0);

	SPVC_EXPORT std::string to_ternary_expression(const SPIRType &result_type, uint32_t select, uint32_t true_value,
	                                  uint32_t false_value);

	SPVC_EXPORT void emit_unary_op(uint32_t result_type, uint32_t result_id, uint32_t op0, const char *op);
	SPVC_EXPORT bool expression_is_forwarded(uint32_t id) const;
	SPVC_EXPORT bool expression_suppresses_usage_tracking(uint32_t id) const;
	SPVC_EXPORT bool expression_read_implies_multiple_reads(uint32_t id) const;
	SPVC_EXPORT SPIRExpression &emit_op(uint32_t result_type, uint32_t result_id, const std::string &rhs, bool forward_rhs,
	                        bool suppress_usage_tracking = false);

	SPVC_EXPORT void access_chain_internal_append_index(std::string &expr, uint32_t base, const SPIRType *type,
	                                        AccessChainFlags flags, bool &access_chain_is_arrayed, uint32_t index);

	SPVC_EXPORT std::string access_chain_internal(uint32_t base, const uint32_t *indices, uint32_t count, AccessChainFlags flags,
	                                  AccessChainMeta *meta);

	SPVC_EXPORT spv::StorageClass get_expression_effective_storage_class(uint32_t ptr);
	SPVC_EXPORT virtual bool access_chain_needs_stage_io_builtin_translation(uint32_t base);

	SPVC_EXPORT virtual void prepare_access_chain_for_scalar_access(std::string &expr, const SPIRType &type,
	                                                    spv::StorageClass storage, bool &is_packed);

	SPVC_EXPORT std::string access_chain(uint32_t base, const uint32_t *indices, uint32_t count, const SPIRType &target_type,
	                         AccessChainMeta *meta = nullptr, bool ptr_chain = false);

	SPVC_EXPORT std::string flattened_access_chain(uint32_t base, const uint32_t *indices, uint32_t count,
	                                   const SPIRType &target_type, uint32_t offset, uint32_t matrix_stride,
	                                   uint32_t array_stride, bool need_transpose);
	SPVC_EXPORT std::string flattened_access_chain_struct(uint32_t base, const uint32_t *indices, uint32_t count,
	                                          const SPIRType &target_type, uint32_t offset);
	SPVC_EXPORT std::string flattened_access_chain_matrix(uint32_t base, const uint32_t *indices, uint32_t count,
	                                          const SPIRType &target_type, uint32_t offset, uint32_t matrix_stride,
	                                          bool need_transpose);
	SPVC_EXPORT std::string flattened_access_chain_vector(uint32_t base, const uint32_t *indices, uint32_t count,
	                                          const SPIRType &target_type, uint32_t offset, uint32_t matrix_stride,
	                                          bool need_transpose);
	SPVC_EXPORT std::pair<std::string, uint32_t> flattened_access_chain_offset(const SPIRType &basetype, const uint32_t *indices,
	                                                               uint32_t count, uint32_t offset,
	                                                               uint32_t word_stride, bool *need_transpose = nullptr,
	                                                               uint32_t *matrix_stride = nullptr,
	                                                               uint32_t *array_stride = nullptr,
	                                                               bool ptr_chain = false);

	SPVC_EXPORT const char *index_to_swizzle(uint32_t index);
	SPVC_EXPORT std::string remap_swizzle(const SPIRType &result_type, uint32_t input_components, const std::string &expr);
	SPVC_EXPORT std::string declare_temporary(uint32_t type, uint32_t id);
	SPVC_EXPORT void emit_uninitialized_temporary(uint32_t type, uint32_t id);
	SPVC_EXPORT SPIRExpression &emit_uninitialized_temporary_expression(uint32_t type, uint32_t id);
	SPVC_EXPORT void append_global_func_args(const SPIRFunction &func, uint32_t index, SmallVector<std::string> &arglist);
	SPVC_EXPORT std::string to_non_uniform_aware_expression(uint32_t id);
	SPVC_EXPORT std::string to_expression(uint32_t id, bool register_expression_read = true);
	SPVC_EXPORT std::string to_composite_constructor_expression(uint32_t id, bool uses_buffer_offset);
	SPVC_EXPORT std::string to_rerolled_array_expression(const std::string &expr, const SPIRType &type);
	SPVC_EXPORT std::string to_enclosed_expression(uint32_t id, bool register_expression_read = true);
	SPVC_EXPORT std::string to_unpacked_expression(uint32_t id, bool register_expression_read = true);
	SPVC_EXPORT std::string to_unpacked_row_major_matrix_expression(uint32_t id);
	SPVC_EXPORT std::string to_enclosed_unpacked_expression(uint32_t id, bool register_expression_read = true);
	SPVC_EXPORT std::string to_dereferenced_expression(uint32_t id, bool register_expression_read = true);
	SPVC_EXPORT std::string to_pointer_expression(uint32_t id, bool register_expression_read = true);
	SPVC_EXPORT std::string to_enclosed_pointer_expression(uint32_t id, bool register_expression_read = true);
	SPVC_EXPORT std::string to_extract_component_expression(uint32_t id, uint32_t index);
	SPVC_EXPORT std::string to_extract_constant_composite_expression(uint32_t result_type, const SPIRConstant &c,
	                                                     const uint32_t *chain, uint32_t length);
	SPVC_EXPORT std::string enclose_expression(const std::string &expr);
	SPVC_EXPORT std::string dereference_expression(const SPIRType &expression_type, const std::string &expr);
	SPVC_EXPORT std::string address_of_expression(const std::string &expr);
	SPVC_EXPORT void strip_enclosed_expression(std::string &expr);
	SPVC_EXPORT std::string to_member_name(const SPIRType &type, uint32_t index);
	SPVC_EXPORT virtual std::string to_member_reference(uint32_t base, const SPIRType &type, uint32_t index, bool ptr_chain);
	SPVC_EXPORT std::string to_multi_member_reference(const SPIRType &type, const SmallVector<uint32_t> &indices);
	SPVC_EXPORT std::string type_to_glsl_constructor(const SPIRType &type);
	SPVC_EXPORT std::string argument_decl(const SPIRFunction::Parameter &arg);
	SPVC_EXPORT virtual std::string to_qualifiers_glsl(uint32_t id);
	SPVC_EXPORT void fixup_io_block_patch_qualifiers(const SPIRVariable &var);
	SPVC_EXPORT void emit_output_variable_initializer(const SPIRVariable &var);
	SPVC_EXPORT std::string to_precision_qualifiers_glsl(uint32_t id);
	SPVC_EXPORT virtual const char *to_storage_qualifiers_glsl(const SPIRVariable &var);
	SPVC_EXPORT std::string flags_to_qualifiers_glsl(const SPIRType &type, const Bitset &flags);
	SPVC_EXPORT const char *format_to_glsl(spv::ImageFormat format);
	SPVC_EXPORT virtual std::string layout_for_member(const SPIRType &type, uint32_t index);
	SPVC_EXPORT virtual std::string to_interpolation_qualifiers(const Bitset &flags);
	SPVC_EXPORT std::string layout_for_variable(const SPIRVariable &variable);
	SPVC_EXPORT std::string to_combined_image_sampler(VariableID image_id, VariableID samp_id);
	SPVC_EXPORT virtual bool skip_argument(uint32_t id) const;
	SPVC_EXPORT virtual void emit_array_copy(const std::string &lhs, uint32_t lhs_id, uint32_t rhs_id,
	                             spv::StorageClass lhs_storage, spv::StorageClass rhs_storage);
	SPVC_EXPORT virtual void emit_block_hints(const SPIRBlock &block);
	SPVC_EXPORT virtual std::string to_initializer_expression(const SPIRVariable &var);
	SPVC_EXPORT virtual std::string to_zero_initialized_expression(uint32_t type_id);
	SPVC_EXPORT bool type_can_zero_initialize(const SPIRType &type) const;

	SPVC_EXPORT bool buffer_is_packing_standard(const SPIRType &type, BufferPackingStandard packing,
	                                uint32_t *failed_index = nullptr, uint32_t start_offset = 0,
	                                uint32_t end_offset = ~(0u));
	SPVC_EXPORT std::string buffer_to_packing_standard(const SPIRType &type, bool support_std430_without_scalar_layout);

	SPVC_EXPORT uint32_t type_to_packed_base_size(const SPIRType &type, BufferPackingStandard packing);
	SPVC_EXPORT uint32_t type_to_packed_alignment(const SPIRType &type, const Bitset &flags, BufferPackingStandard packing);
	SPVC_EXPORT uint32_t type_to_packed_array_stride(const SPIRType &type, const Bitset &flags, BufferPackingStandard packing);
	SPVC_EXPORT uint32_t type_to_packed_size(const SPIRType &type, const Bitset &flags, BufferPackingStandard packing);
	SPVC_EXPORT uint32_t type_to_location_count(const SPIRType &type) const;

	SPVC_EXPORT std::string bitcast_glsl(const SPIRType &result_type, uint32_t arg);
	SPVC_EXPORT virtual std::string bitcast_glsl_op(const SPIRType &result_type, const SPIRType &argument_type);

	SPVC_EXPORT std::string bitcast_expression(SPIRType::BaseType target_type, uint32_t arg);
	SPVC_EXPORT std::string bitcast_expression(const SPIRType &target_type, SPIRType::BaseType expr_type, const std::string &expr);

	SPVC_EXPORT std::string build_composite_combiner(uint32_t result_type, const uint32_t *elems, uint32_t length);
	SPVC_EXPORT bool remove_duplicate_swizzle(std::string &op);
	SPVC_EXPORT bool remove_unity_swizzle(uint32_t base, std::string &op);

	// Can modify flags to remote readonly/writeonly if image type
	// and force recompile.
	SPVC_EXPORT bool check_atomic_image(uint32_t id);

	SPVC_EXPORT virtual void replace_illegal_names();
	SPVC_EXPORT void replace_illegal_names(const std::unordered_set<std::string> &keywords);
	SPVC_EXPORT virtual void emit_entry_point_declarations();

	SPVC_EXPORT void replace_fragment_output(SPIRVariable &var);
	SPVC_EXPORT void replace_fragment_outputs();
	SPVC_EXPORT std::string legacy_tex_op(const std::string &op, const SPIRType &imgtype, uint32_t id);

	uint32_t indent = 0;

	std::unordered_set<uint32_t> emitted_functions;

	// Ensure that we declare phi-variable copies even if the original declaration isn't deferred
	std::unordered_set<uint32_t> flushed_phi_variables;

	std::unordered_set<uint32_t> flattened_buffer_blocks;
	std::unordered_map<uint32_t, bool> flattened_structs;

	ShaderSubgroupSupportHelper shader_subgroup_supporter;

	SPVC_EXPORT std::string load_flattened_struct(const std::string &basename, const SPIRType &type);
	SPVC_EXPORT std::string to_flattened_struct_member(const std::string &basename, const SPIRType &type, uint32_t index);
	SPVC_EXPORT void store_flattened_struct(uint32_t lhs_id, uint32_t value);
	SPVC_EXPORT void store_flattened_struct(const std::string &basename, uint32_t rhs, const SPIRType &type,
	                            const SmallVector<uint32_t> &indices);
	SPVC_EXPORT std::string to_flattened_access_chain_expression(uint32_t id);

	// Usage tracking. If a temporary is used more than once, use the temporary instead to
	// avoid AST explosion when SPIRV is generated with pure SSA and doesn't write stuff to variables.
	std::unordered_map<uint32_t, uint32_t> expression_usage_counts;
	SPVC_EXPORT void track_expression_read(uint32_t id);

	SmallVector<std::string> forced_extensions;
	SmallVector<std::string> header_lines;

	// Used when expressions emit extra opcodes with their own unique IDs,
	// and we need to reuse the IDs across recompilation loops.
	// Currently used by NMin/Max/Clamp implementations.
	std::unordered_map<uint32_t, uint32_t> extra_sub_expressions;

	SmallVector<TypeID> workaround_ubo_load_overload_types;
	SPVC_EXPORT void request_workaround_wrapper_overload(TypeID id);
	SPVC_EXPORT void rewrite_load_for_wrapped_row_major(std::string &expr, TypeID loaded_type, ID ptr);

	uint32_t statement_count = 0;

	inline bool is_legacy() const
	{
		return (options.es && options.version < 300) || (!options.es && options.version < 130);
	}

	inline bool is_legacy_es() const
	{
		return options.es && options.version < 300;
	}

	inline bool is_legacy_desktop() const
	{
		return !options.es && options.version < 130;
	}

	bool requires_transpose_2x2 = false;
	bool requires_transpose_3x3 = false;
	bool requires_transpose_4x4 = false;
	bool ray_tracing_is_khr = false;
	SPVC_EXPORT void ray_tracing_khr_fixup_locations();

	SPVC_EXPORT bool args_will_forward(uint32_t id, const uint32_t *args, uint32_t num_args, bool pure);
	SPVC_EXPORT void register_call_out_argument(uint32_t id);
	SPVC_EXPORT void register_impure_function_call();
	SPVC_EXPORT void register_control_dependent_expression(uint32_t expr);

	// GL_EXT_shader_pixel_local_storage support.
	std::vector<PlsRemap> pls_inputs;
	std::vector<PlsRemap> pls_outputs;
	SPVC_EXPORT std::string pls_decl(const PlsRemap &variable);
	SPVC_EXPORT const char *to_pls_qualifiers_glsl(const SPIRVariable &variable);
	SPVC_EXPORT void emit_pls();
	SPVC_EXPORT void remap_pls_variables();

	// GL_EXT_shader_framebuffer_fetch support.
	std::vector<std::pair<uint32_t, uint32_t>> subpass_to_framebuffer_fetch_attachment;
	std::vector<std::pair<uint32_t, bool>> inout_color_attachments;
	SPVC_EXPORT bool location_is_framebuffer_fetch(uint32_t location) const;
	SPVC_EXPORT bool location_is_non_coherent_framebuffer_fetch(uint32_t location) const;
	SPVC_EXPORT bool subpass_input_is_framebuffer_fetch(uint32_t id) const;
	SPVC_EXPORT void emit_inout_fragment_outputs_copy_to_subpass_inputs();
	SPVC_EXPORT const SPIRVariable *find_subpass_input_by_attachment_index(uint32_t index) const;
	SPVC_EXPORT const SPIRVariable *find_color_output_by_location(uint32_t location) const;

	// A variant which takes two sets of name. The secondary is only used to verify there are no collisions,
	// but the set is not updated when we have found a new name.
	// Used primarily when adding block interface names.
	SPVC_EXPORT void add_variable(std::unordered_set<std::string> &variables_primary,
	                  const std::unordered_set<std::string> &variables_secondary, std::string &name);

	SPVC_EXPORT void check_function_call_constraints(const uint32_t *args, uint32_t length);
	SPVC_EXPORT void handle_invalid_expression(uint32_t id);
	SPVC_EXPORT void find_static_extensions();

	SPVC_EXPORT std::string emit_for_loop_initializers(const SPIRBlock &block);
	SPVC_EXPORT void emit_while_loop_initializers(const SPIRBlock &block);
	SPVC_EXPORT bool for_loop_initializers_are_same_type(const SPIRBlock &block);
	SPVC_EXPORT bool optimize_read_modify_write(const SPIRType &type, const std::string &lhs, const std::string &rhs);
	SPVC_EXPORT void fixup_image_load_store_access();

	SPVC_EXPORT bool type_is_empty(const SPIRType &type);

	SPVC_EXPORT virtual void declare_undefined_values();

	SPVC_EXPORT bool can_use_io_location(spv::StorageClass storage, bool block);
	SPVC_EXPORT const Instruction *get_next_instruction_in_block(const Instruction &instr);
	SPVC_EXPORT static uint32_t mask_relevant_memory_semantics(uint32_t semantics);

	SPVC_EXPORT std::string convert_half_to_string(const SPIRConstant &value, uint32_t col, uint32_t row);
	SPVC_EXPORT std::string convert_float_to_string(const SPIRConstant &value, uint32_t col, uint32_t row);
	SPVC_EXPORT std::string convert_double_to_string(const SPIRConstant &value, uint32_t col, uint32_t row);

	SPVC_EXPORT std::string convert_separate_image_to_expression(uint32_t id);

	// Builtins in GLSL are always specific signedness, but the SPIR-V can declare them
	// as either unsigned or signed.
	// Sometimes we will need to automatically perform casts on load and store to make this work.
	SPVC_EXPORT virtual void cast_to_builtin_store(uint32_t target_id, std::string &expr, const SPIRType &expr_type);
	SPVC_EXPORT virtual void cast_from_builtin_load(uint32_t source_id, std::string &expr, const SPIRType &expr_type);
	SPVC_EXPORT void unroll_array_from_complex_load(uint32_t target_id, uint32_t source_id, std::string &expr);
	SPVC_EXPORT bool unroll_array_to_complex_store(uint32_t target_id, uint32_t source_id);
	SPVC_EXPORT void convert_non_uniform_expression(std::string &expr, uint32_t ptr_id);

	SPVC_EXPORT void handle_store_to_invariant_variable(uint32_t store_id, uint32_t value_id);
	SPVC_EXPORT void disallow_forwarding_in_expression_chain(const SPIRExpression &expr);

	SPVC_EXPORT bool expression_is_constant_null(uint32_t id) const;
	SPVC_EXPORT bool expression_is_non_value_type_array(uint32_t ptr);
	SPVC_EXPORT virtual void emit_store_statement(uint32_t lhs_expression, uint32_t rhs_expression);

	SPVC_EXPORT uint32_t get_integer_width_for_instruction(const Instruction &instr) const;
	SPVC_EXPORT uint32_t get_integer_width_for_glsl_instruction(GLSLstd450 op, const uint32_t *arguments, uint32_t length) const;

	SPVC_EXPORT bool variable_is_lut(const SPIRVariable &var) const;

	char current_locale_radix_character = '.';

	SPVC_EXPORT void fixup_type_alias();
	SPVC_EXPORT void reorder_type_alias();

	SPVC_EXPORT static const char *vector_swizzle(int vecsize, int index);

	SPVC_EXPORT bool is_stage_output_location_masked(uint32_t location, uint32_t component) const;
	SPVC_EXPORT bool is_stage_output_builtin_masked(spv::BuiltIn builtin) const;
	SPVC_EXPORT bool is_stage_output_variable_masked(const SPIRVariable &var) const;
	SPVC_EXPORT bool is_stage_output_block_member_masked(const SPIRVariable &var, uint32_t index, bool strip_array) const;
	SPVC_EXPORT uint32_t get_accumulated_member_location(const SPIRVariable &var, uint32_t mbr_idx, bool strip_array) const;
	SPVC_EXPORT uint32_t get_declared_member_location(const SPIRVariable &var, uint32_t mbr_idx, bool strip_array) const;
	std::unordered_set<LocationComponentPair, InternalHasher> masked_output_locations;
	std::unordered_set<uint32_t> masked_output_builtins;

private:
	SPVC_EXPORT void init();
};
} // namespace SPIRV_CROSS_NAMESPACE

#endif
