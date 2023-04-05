#pragma once
#ifndef __INode_h__
#define __INode_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#include <xmp/XMPCore/XMPCoreFwdDeclarations.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/ISharedObject.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/IVersionable.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/IThreadSafe.h>

namespace AdobeXMPCore {
	class INodeProxy;
	//!
	//! \brief Version1 of the interface that serves as a base interface to all types of nodes in the XMP DOM.
	//! \details Provides all the functions to get various properties of the node.
	//! \attention Support multi threading through locks but can be enabled/disabled by the client. By default
	//!  every object created does not support multi-threading.
	//!
	class INode_v1
		: public virtual ISharedObject
		, public virtual IVersionable
		, public virtual IThreadSafe
	{
		friend class INodeProxy;
	public:

		//!
		//! @brief Indicates various types of node available in XMP Data Model like simple, array and structure.
		//!
		typedef enum {
			//! Indicates none, to be used as invalid type.
			kNTNone = 0,

			//! XMP Node is of Simple Node type (key value pair).
			kNTSimple = 1,

			//! XMP Node is of Array type. Indexing start from 1.
			kNTArray = 1 << 1,

			//! XMP Node is of structure type. 
			kNTStructure = 1 << 2,

			//! XMP Node of any type
			kNTAll = kAllBits
		} eNodeType;

		//!
		//! @brief Gets the node type of the node.
		//! \return An object of type \#eNodeType indicating the type of the node.
		//!
		virtual eNodeType GetNodeType() const = 0;

		//!
		//! @brief Gets the node type of the node's parent.
		//! \return An object of type \#eNodeType indicating the type of the node.
		//! \note \#eNodeType::kNTNone is returned in case node has no parent.
		//!
		virtual eNodeType GetParentNodeType() const = 0;

		//!
		//! @{
		//! @brief Gets the parent node of the node.
		//! \return Either a const or non const pointer to INode interface.
		//! \return A shared pointer to either a const or non const \#AdobeXMPCore::INode representing the parent of the node.
		//! \note Returns an invalid shared pointer in case the node is a root node or it is not part of tree.
		//!
		XMP_PRIVATE spcINode GetParent() const {
			return const_cast< INode_v1 * >( this )->GetParent();
		}
		virtual spINode GetParent() = 0;
		//!
		//! @}

		//!
		//!  @brief Changes the local name of the node.
		//! \param[in] name Pointer to a constant char buffer containing local name of the node.
		//! \param[in] nameLength Number of characters in name. In case name is null terminated set it to \#AdobeXMPCommon::npos.
		//! \attention Error can be thrown in case
		//!		- name is NULL pointer or its contents are empty
		//!		- name is not valid XML property name.
		//!		- Sibling with the same combination of name and nameSpace is present.
		//!
		virtual void SetName( const char * name, sizet nameLength ) = 0;

		//!
		//! @brief Gets the local name of the node.
		//! \return a shared pointer to const \#AdobeXMPCommon::IUTF8String representing the name of the node.
		//!
		virtual spcIUTF8String GetName() const = 0;

		//!
		//! @brief Changes the name space of the node.
		//! \param[in] nameSpace Pointer to a constant char buffer containing name space URI of the node.
		//! \param[in] nameSpaceLength Number of characters in nameSpace. In case nameSpace is null terminated set it to \#AdobeXMPCommon::npos.
		//! \attention Error can be thrown in case
		//!		- nameSpace is NULL pointer or its contents are empty
		//!		- Sibling with the same combination of name and nameSpace is present.
		//!
		virtual void SetNameSpace( const char * nameSpace, sizet nameSpaceLength ) = 0;

		//!
		//! @brief Gets the name space of the node.
		//! \return A shared pointer to const \#AdobeXMPCommon::IUTF8String representing the name space of the node.
		//!
		virtual spcIUTF8String GetNameSpace() const = 0;

		//!
		//! @brief Gets the path of the node from the root of the metadata.
		//! \return A shared pointer to \#AdobeXMPCore::IPath representing the path of the node.
		//!
		virtual spIPath GetPath() const = 0;

		//!
		//! @brief Gets the count of the qualifiers attached with the node
		//! \return An object of type \#AdobeXMPCommon::sizet containing the count of qualifiers attached with the node.
		//!
		virtual sizet QualifiersCount() const __NOTHROW__ = 0;

		//!
		//! @{
		//!  Get an iterator object to iterate over all the qualifier nodes attached to the composite node.
		//! \return A shared pointer to a const or non const \#INodeIterator object.
		//!
		XMP_PRIVATE spcINodeIterator QualifiersIterator() const {
			return const_cast< INode_v1 * >( this )->QualifiersIterator();
		}
		virtual spINodeIterator QualifiersIterator() = 0;
		//! @}

		//!
		//! @brief Gets the type of the node's qualifier having specified namespace and name.
		//! \param[in] nameSpace Pointer to a constant char buffer containing name space URI of the qualifier node.
		//! \param[in] nameSpaceLength Number of characters in nameSpace. In case nameSpace is null terminated set it to \#AdobeXMPCommon::npos.
		//! \param[in] name Pointer to a constant char buffer containing local name of the qualifier node.
		//! \param[in] nameLength Number of characters in name. In case name is null terminated set it to \#AdobeXMPCommon::npos.
		//! \return An object of type \#eNodeType indicating the type of the node's qualifier.
		//! \note In case no qualifier exists with the specified nameSpace and name combination then an \#eNodeType::kNTNode is returned.
		//!
		virtual eNodeType GetQualifierNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const = 0;

		//!
		//! @{
		//! @brief Gets the qualifier of the node having specified namespace and name.
		//! \param[in] nameSpace Pointer to a constant char buffer containing name space URI of the qualifier node.
		//! \param[in] nameSpaceLength Number of characters in nameSpace. In case nameSpace is null terminated set it to \#AdobeXMPCommon::npos.
		//! \param[in] name Pointer to a constant char buffer containing local name of the qualifier node.
		//! \param[in] nameLength Number of characters in name. In case name is null terminated set it to \#AdobeXMPCommon::npos.
		//! \return A shared pointer to either a const or const qualifier node.
		//! \note In case no qualifier exists with the specified nameSpace and name combination then an invalid shared pointer
		//!       is returned.
		//!
		XMP_PRIVATE spcINode GetQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const {
			return const_cast< INode_v1 * >( this )->GetQualifier( nameSpace, nameSpaceLength, name, nameLength );
		}
		virtual spINode GetQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) = 0;
		//! @}

		//!
		//! @{
		//! @brief Get the node's qualifier having specified name space and name as simple node.
		//! \param[in] nameSpace Pointer to a constant char buffer containing name space URI of the qualifier node.
		//! \param[in] nameSpaceLength Number of characters in nameSpace. In case nameSpace is null terminated set it to \#AdobeXMPCommon::npos.
		//! \param[in] name Pointer to a constant char buffer containing local name of the qualifier node.
		//! \param[in] nameLength Number of characters in name. In case name is null terminated set it to \#AdobeXMPCommon::npos.
		//! \return A shared pointer to const or non const \#ISimpleNode object containing qualifier.
		//! \note In case no qualifier exists with the specified nameSpace and name combination then an invalid shared pointer
		//!       is returned.
		//! \attention Error is thrown in case 
		//!		- a qualifier exists with the specified nameSpace and name combination but is not a simple node.
		//!
		XMP_PRIVATE spcISimpleNode GetSimpleQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const {
			auto node = GetQualifier( nameSpace, nameSpaceLength, name, nameLength );
			if ( node ) return node->ConvertToSimpleNode();
			return spcISimpleNode();
		}

		XMP_PRIVATE spISimpleNode GetSimpleQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) {
			auto node = GetQualifier( nameSpace, nameSpaceLength, name, nameLength );
			if ( node ) return node->ConvertToSimpleNode();
			return spISimpleNode();
		}
		//! @}

		//!
		//! @{
		//! @brief Get the node's qualifier having specified name space and name as structure node.
		//! \param[in] nameSpace Pointer to a constant char buffer containing name space URI of the qualifier node.
		//! \param[in] nameSpaceLength Number of characters in nameSpace. In case nameSpace is null terminated set it to \#AdobeXMPCommon::npos.
		//! \param[in] name Pointer to a constant char buffer containing local name of the qualifier node.
		//! \param[in] nameLength Number of characters in name. In case name is null terminated set it to \#AdobeXMPCommon::npos.
		//! \return A shared pointer to const or non const \#IStructureNode object containing qualifier.
		//! \note In case no qualifier exists with the specified nameSpace and name combination then an invalid shared pointer
		//!       is returned.
		//! \attention Error is thrown in case 
		//!		- a qualifier exists with the specified nameSpace and name combination but is not a structure node.
		//!
		XMP_PRIVATE spcIStructureNode GetStructureQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const {
			auto node = GetQualifier( nameSpace, nameSpaceLength, name, nameLength );
			if ( node ) return node->ConvertToStructureNode();
			return spcIStructureNode();
		}

		XMP_PRIVATE spIStructureNode GetStructureQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) {
			auto node = GetQualifier( nameSpace, nameSpaceLength, name, nameLength );
			if ( node ) return node->ConvertToStructureNode();
			return spIStructureNode();
		}
		//! @}

		//!
		//! @{
		//! @brief Get the node's qualifier having specified name space and name as an array node.
		//! \param[in] nameSpace Pointer to a constant char buffer containing name space URI of the qualifier node.
		//! \param[in] nameSpaceLength Number of characters in nameSpace. In case nameSpace is null terminated set it to \#AdobeXMPCommon::npos.
		//! \param[in] name Pointer to a constant char buffer containing local name of the qualifier node.
		//! \param[in] nameLength Number of characters in name. In case name is null terminated set it to \#AdobeXMPCommon::npos.
		//! \return A shared pointer to const or non const \#ISimpleNode object containing qualifier.
		//! \note In case no qualifier exists with the specified nameSpace and name combination then an invalid shared pointer
		//!       is returned.
		//! \attention Error is thrown in case 
		//!		- a qualifier exists with the specified nameSpace and name combination but is not an array node.
		//!
		XMP_PRIVATE spcIArrayNode GetArrayQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const {
			auto node = GetQualifier( nameSpace, nameSpaceLength, name, nameLength );
			if ( node ) return node->ConvertToArrayNode();
			return spcIArrayNode();
		}

		XMP_PRIVATE spIArrayNode GetArrayQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) {
			auto node = GetQualifier( nameSpace, nameSpaceLength, name, nameLength );
			if ( node ) return node->ConvertToArrayNode();
			return spIArrayNode();
		}
		//! @}

		//!
		//! @brief Inserts a given qualifier node.
		//! \param[in] node Shared pointer to an object of \#AdobeXMPCore::INode representing the qualifier node to be inserted.
		//! \attention Error is thrown in following cases:
		//!		- given qualifier node is invalid.
		//!		- given qualifier node is already a child of some other node.
		//!		- there exists a qualifier node with the same nameSpace and name combination.
		//!		- parent or any ancestor node is a qualifier node.
		//!
		virtual void InsertQualifier( const spINode & node ) = 0;

		//!
		//! @brief Replaces a given qualifier node.
		//! \param[in] node Shared pointer to an object of \#AdobeXMPCore::INode representing the qualifier node to be inserted.
		//! \return A shared pointer to a qualifier node which is being replaced.
		//! \attention Error is thrown in following cases:
		//!		-# given qualifier node is invalid.
		//!		-# given qualifier node is already a child of some other node.
		//!		-# there exists no qualifier node with the same nameSpace and name combination.
		//! \note Warning is raised in case the type of the old existing node is not same as that of new node.
		//!
		virtual spINode ReplaceQualifier( const spINode & node ) = 0;

		//!
		//! @brief Removes the qualifier node with the specified nameSpace and name.
		//! \param[in] nameSpace Pointer to a constant char buffer containing name space URI of the qualifier node.
		//! \param[in] nameSpaceLength Number of characters in nameSpace. In case nameSpace is null terminated set it to \#AdobeXMPCommon::npos.
		//! \param[in] name Pointer to a constant char buffer containing local name of the qualifier node.
		//! \param[in] nameLength Number of characters in name. In case name is null terminated set it to \#AdobeXMPCommon::npos.
		//! \return A shared pointer to \#AdobeXMPCore::INode object representing qualifier node which is removed from the node.
		//! \note In case no qualifier node exists at the given index an invalid shared pointer is returned.
		//!
		virtual spINode RemoveQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) = 0;

		//!
		//! @brief Indicates whether the node is a direct child of an array node.
		//! \return A bool value; true in case the node is a direct child of an array node, false otherwise.
		//!
		virtual bool IsArrayItem() const = 0;

		//!
		//! @brief Indicates whether the node is a qualifier node.
		//! \return A bool value; true in case the node is a qualifier node, false otherwise.
		//!
		virtual bool IsQualifierNode() const = 0;

		//!
		//! @brief Returns the index of the node in case it is an array item.
		//! \return The index of the node, in case it is an array item, otherwise returns 0.
		//!
		virtual sizet GetIndex() const = 0;

		//!
		//! @brief Indicates whether the node has any qualifiers associated with it.
		//! \return A bool value; true in case the node has any qualifier associated with it, false otherwise.
		//!
		virtual bool HasQualifiers() const = 0;

		//!
		//! @brief Returns whether the node has any content or not.
		//! return A bool value indicating the presence of contents in the node apart from qualifiers.
		//!
		virtual bool HasContent() const = 0;

		//!
		//! @brief Returns whether the node is empty.
		//! return A bool value indicating whether the contents and qualifiers of a node are empty.
		//!
		virtual bool IsEmpty() const = 0;

		//!
		//! @brief Returns the status about any change done to the node or its children or qualifiers.
		//! returns a bool value indicating whether some changes have been performed on the node or its children or qualifiers.
		//! for a simple node, true will be returned in scenarios like when the node's value or qualifiers are modified.
		//! for an array node or a structure node, true will be returned in scenarios like when the node's children or the node's qualifiers are modified.
		//!
		virtual bool HasChanged() const = 0;

		//!
		//! @brief Acknowledges that changes for the node and its children and qualifiers have been taken care of.
		//! for a simple node, changes that will be acknowledged in scenarios like when the node's value or node's qualifiers were modified.
		//! for an array node or a structure node, changes will be acknowledged in scenarios like when the node's children were or the node's qualifiers were modified.
		//!
		virtual void AcknowledgeChanges() const __NOTHROW__ = 0;

		//!
		//! @brief Clear the contents of the node.
		//! \param[in] contents A bool value controlling whether contents of the node should be cleared or not.
		//! \param[in] qualifiers A bool value controlling whether qualifiers of the node should be cleared or not.
		//!
		virtual void Clear( bool contents = true, bool qualifiers = true ) = 0;

		//!
		//! @{
		//! @brief Converts Node to a simple node, if possible.
		//! \return Shared pointer to const or non const ISimpleNode object. An empty simple node is thrown in case actual node is not a simple node.
		//!
		XMP_PRIVATE spcISimpleNode ConvertToSimpleNode() const {
			return const_cast< INode_v1 * >( this )->ConvertToSimpleNode();
		}
		virtual spISimpleNode ConvertToSimpleNode() = 0;
		//! @}

		//!
		//! @{
		//! @brief Converts Node to a structure node type, if possible.
		//! \return Shared pointer to const or non const IStructureNode object. An empty structure node is thrown in case actual node is not a structure node.
		//!
		XMP_PRIVATE spcIStructureNode ConvertToStructureNode() const {
			return const_cast< INode_v1 * >( this )->ConvertToStructureNode();
		}
		virtual spIStructureNode ConvertToStructureNode() = 0;
		//! @}

		//!
		//! @{
		//! @brief Converts Node to an array node type, if possible.
		//! \return Shared pointer to const or non const IArrayNode object. An empty array node is thrown in case actual node is not an array node.
		//!
		XMP_PRIVATE spcIArrayNode ConvertToArrayNode() const {
			return const_cast< INode_v1 * >( this )->ConvertToArrayNode();
		}
		virtual spIArrayNode ConvertToArrayNode() = 0;
		//! @}

		//!
		//! @{
		//! @brief Converts Node to a metadata node type, if possible.
		//! \return Shared pointer to const or non const IMetadata object. An empty metadata node is thrown in case actual node is not a metadata node.
		//!
		XMP_PRIVATE spcIMetadata ConvertToMetadata() const {
			return const_cast< INode_v1 * >( this )->ConvertToMetadata();
		}
		virtual spIMetadata ConvertToMetadata() = 0;
		//! @}

		//!
		//! @brief Virtual copy constructor
		//! @details Clones the node creating an exact replica of the node which is not part of any metadata tree.
		//! \param[in] ignoreEmptyNodes A bool value controlling whether to clone empty nodes or not.
		//! \param[in] ignoreNodesWithOnlyQualifiers A bool value controlling whether presence of only qualifiers should mark
		//!                                          node as non empty.
		//! \return A shared pointer to newly created replica of the node.
		//!
		virtual spINode Clone( bool ignoreEmptyNodes = false, bool ignoreNodesWithOnlyQualifiers = false ) const = 0;

		//!
		//! \cond XMP_INTERNAL_DOCUMENTATION

		//!
		//! @{
		//! @brief Returns the actual raw pointer from the shared pointer, which can be a shared pointer of a proxy class.
		//! \return Either a const or non const pointer to INode interface.
		//!
		virtual pINode GetActualINode() __NOTHROW__ = 0;

		XMP_PRIVATE pcINode GetActualINode() const __NOTHROW__ {
			return const_cast< INode_v1 * >( this )->GetActualINode();
		}
		//!
		//! @}

		//!
		//! @{
		//! @brief Returns the pointer to internal interfaces.
		//! \return Either a const or non const pointer to INode_I interface.
		//!
		virtual AdobeXMPCore_Int::pINode_I GetINode_I() __NOTHROW__ = 0;

		XMP_PRIVATE AdobeXMPCore_Int::pcINode_I GetINode_I() const __NOTHROW__ {
			return const_cast< INode_v1 * >( this )->GetINode_I();
		}
		//!
		//! @}

		//!
		//! @{
		//! @brief Converts raw pointer to shared pointer. The raw pointer is of version 1 interface
		//!        where as the returned shared pointer depends on the version client is interested in.
		//! \return Shared pointer to const or non constant interface.
		//!
		HXMP_EXPORT static spINode MakeShared( pINode_base ptr );
		XMP_PRIVATE static spcINode MakeShared( pcINode_base ptr ) {
			return MakeShared( const_cast< pINode_base >( ptr ) );
		}
		//!
		//! @}

		//!
		//! @brief Returns the unique ID assigned to the interface.
		//! \return 64 bit unsigned integer representing the unique ID assigned to the interface.
		//!
		XMP_PRIVATE static uint64 GetInterfaceID() { return kINodeID; }

		//!
		//! @brief Returns the version of the interface.
		//! \return 32 bit unsigned integer representing the version of the interface.
		//!
		XMP_PRIVATE static uint32 GetInterfaceVersion() { return 1; }
		//! \endcond

	protected:
		//!
		//! Destructor
		//! 
		virtual ~INode_v1() __NOTHROW__ {}

		//! \cond XMP_INTERNAL_DOCUMENTATION
		virtual uint32 getParentNodeType( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pINode_base getParent( pcIError_base & error ) __NOTHROW__ = 0;
		virtual void setName( const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pcIUTF8String_base getName( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void setNameSpace( const char * nameSpace, sizet nameSpaceLength, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pcIUTF8String_base getNameSpace( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIPath_base getPath( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pINodeIterator_base qualifiersIterator( pcIError_base & error ) __NOTHROW__ = 0;
		virtual uint32 getQualifierNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pINode_base getQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__ = 0;
		virtual void insertQualifier( pINode_base base, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pINode_base replaceQualifier( pINode_base node, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pINode_base removeQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__ = 0;
		virtual uint32 getNodeType( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual uint32 isArrayItem( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual uint32 isQualifierNode( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual sizet getIndex( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual uint32 hasQualifiers( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual uint32 hasContent( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual uint32 isEmpty( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual uint32 hasChanged( pcIError_base & error ) const __NOTHROW__ = 0;
		virtual void clear( uint32 contents, uint32 qualifiers, pcIError_base & error ) __NOTHROW__ = 0;
		virtual pINode_base clone( uint32 igoreEmptyNodes, uint32 ignoreNodesWithOnlyQualifiers, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pISimpleNode_base convertToSimpleNode( pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIStructureNode_base convertToStructureNode( pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIArrayNode_base convertToArrayNode( pcIError_base & error ) __NOTHROW__ = 0;
		virtual pIMetadata_base convertToMetadata( pcIError_base & error ) __NOTHROW__ = 0;

		//! @}

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
		//! \endcond

	};
}

//! \cond XMP_INTERNAL_DOCUMENTATION

	namespace AdobeXMPCore {

		class INodeProxy
			: public virtual INode
		{
		private:
			pINode mRawPtr;

		public:
			HXMP_INLINE_DECL INodeProxy( pINode ptr );
			HXMP_INLINE_DECL ~INodeProxy() __NOTHROW__ ;

			HXMP_INLINE_DECL pINode GetActualINode() __NOTHROW__;
			HXMP_INLINE_DECL void Acquire() const __NOTHROW__;
			HXMP_INLINE_DECL void Release() const __NOTHROW__;

			HXMP_INLINE_DECL AdobeXMPCommon_Int::pISharedObject_I GetISharedObject_I() __NOTHROW__;
			HXMP_INLINE_DECL AdobeXMPCore_Int::pINode_I GetINode_I() __NOTHROW__;

			HXMP_INLINE_DECL pvoid GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion );

			HXMP_INLINE_DECL virtual eNodeType GetParentNodeType() const;
			HXMP_INLINE_DECL virtual spINode GetParent();
			HXMP_INLINE_DECL virtual void SetName( const char * name, sizet nameLength );
			HXMP_INLINE_DECL virtual spcIUTF8String GetName() const;
			HXMP_INLINE_DECL virtual void SetNameSpace( const char * nameSpace, sizet nameSpaceLength );
			HXMP_INLINE_DECL virtual spcIUTF8String GetNameSpace() const;
			HXMP_INLINE_DECL virtual spIPath GetPath() const;
			HXMP_INLINE_DECL virtual sizet QualifiersCount() const __NOTHROW__;
			HXMP_INLINE_DECL virtual spINodeIterator QualifiersIterator();
			HXMP_INLINE_DECL virtual eNodeType GetQualifierNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const;
			HXMP_INLINE_DECL virtual spINode GetQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength );
			HXMP_INLINE_DECL virtual void InsertQualifier( const spINode & node );
			HXMP_INLINE_DECL virtual spINode ReplaceQualifier( const spINode & node );
			HXMP_INLINE_DECL virtual spINode RemoveQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength );
			HXMP_INLINE_DECL virtual eNodeType GetNodeType() const;
			HXMP_INLINE_DECL virtual bool IsArrayItem() const;
			HXMP_INLINE_DECL virtual bool IsQualifierNode() const;
			HXMP_INLINE_DECL virtual sizet GetIndex() const;
			HXMP_INLINE_DECL virtual bool HasQualifiers() const;
			HXMP_INLINE_DECL virtual bool HasContent() const;
			HXMP_INLINE_DECL virtual bool IsEmpty() const;
			HXMP_INLINE_DECL virtual bool HasChanged() const;
			HXMP_INLINE_DECL virtual void AcknowledgeChanges() const __NOTHROW__;
			HXMP_INLINE_DECL virtual void Clear( bool contents, bool qualifiers );
			HXMP_INLINE_DECL virtual spINode Clone( bool ignoreEmptyNodes, bool ignoreNodesWithOnlyQualifiers ) const;
			HXMP_INLINE_DECL virtual void EnableThreadSafety() const __NOTHROW__;
			HXMP_INLINE_DECL virtual void DisableThreadSafety() const __NOTHROW__;
			HXMP_INLINE_DECL virtual bool IsThreadSafe() const;
			HXMP_INLINE_DECL virtual AdobeXMPCommon_Int::pIThreadSafe_I GetIThreadSafe_I() __NOTHROW__;
			HXMP_INLINE_DECL virtual spISimpleNode ConvertToSimpleNode();
			HXMP_INLINE_DECL virtual spIStructureNode ConvertToStructureNode();
			HXMP_INLINE_DECL virtual spIArrayNode ConvertToArrayNode();
			HXMP_INLINE_DECL virtual spIMetadata ConvertToMetadata();

		protected:
			HXMP_INLINE_DECL virtual pINode_base getParent( pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual void setName( const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual pcIUTF8String_base getName( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual void setNameSpace( const char * nameSpace, sizet nameSpaceLength, pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual pcIUTF8String_base getNameSpace( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual pIPath_base getPath( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual pINodeIterator_base qualifiersIterator( pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual pINode_base getQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual void insertQualifier( pINode_base base, pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual pINode_base replaceQualifier( pINode_base node, pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual pINode_base removeQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 getNodeType( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 isArrayItem( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 isQualifierNode( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual sizet getIndex( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 hasQualifiers( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 hasContent( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 isEmpty( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 hasChanged( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual void clear( uint32 contents, uint32 qualifiers, pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual pINode_base clone( uint32 igoreEmptyNodes, uint32 ignoreNodesWithOnlyQualifiers, pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 isThreadSafe() const __NOTHROW__;
			HXMP_INLINE_DECL virtual pISimpleNode_base convertToSimpleNode( pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual pIStructureNode_base convertToStructureNode( pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual pIArrayNode_base convertToArrayNode( pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual pIMetadata_base convertToMetadata( pcIError_base & error ) __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 getParentNodeType( pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL virtual uint32 getQualifierNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) const __NOTHROW__;
			HXMP_INLINE_DECL pvoid getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__;
		};

}

//! \endcond

#endif  // __INode_h__
