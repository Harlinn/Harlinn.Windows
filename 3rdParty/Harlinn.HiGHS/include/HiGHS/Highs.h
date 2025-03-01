/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2024 by Julian Hall, Ivet Galabova,    */
/*    Leona Gottwald and Michael Feldmeier                               */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file Highs.h
 * @brief The HiGHS class
 */
#ifndef HIGHS_H_
#define HIGHS_H_

#include <sstream>

#include "lp_data/HighsCallback.h"
#include "lp_data/HighsLpUtils.h"
#include "lp_data/HighsRanging.h"
#include "lp_data/HighsSolutionDebug.h"
#include "model/HighsModel.h"
#include "presolve/ICrash.h"
#include "presolve/PresolveComponent.h"

/**
 * @brief Return the version
 */
const char* highsVersion();

/**
 * @brief Return detailed version information, githash and compilation
 * date
 */
HighsInt highsVersionMajor();
HighsInt highsVersionMinor();
HighsInt highsVersionPatch();
const char* highsGithash();

/**
 * @brief Class to set parameters and run HiGHS
 */
class Highs {
 public:
  HIGHS_EXPORT Highs();
  virtual ~Highs() {
    FILE* log_stream = options_.log_options.log_stream;
    if (log_stream != nullptr) {
      assert(log_stream != stdout);
      fclose(log_stream);
    }
  }

  /**
   * @brief Return the version as a string
   */
  std::string version() const { return highsVersion(); }

  /**
   * @brief Return major version
   */
  HighsInt versionMajor() const { return highsVersionMajor(); }

  /**
   * @brief Return minor version
   */
  HighsInt versionMinor() const { return highsVersionMinor(); }

  /**
   * @brief Return patch version
   */
  HighsInt versionPatch() const { return highsVersionPatch(); }

  /**
   * @brief Return githash
   */
  std::string githash() const { return highsGithash(); }

  /**
   * @brief Reset the options and then call clearModel()
   */
  HIGHS_EXPORT HighsStatus clear();

  /**
   * @brief Clear the incumbent model and then call clearSolver()
   */
  HIGHS_EXPORT HighsStatus clearModel();

  /**
   * @brief Clear all solution data associated with the model
   */
  HIGHS_EXPORT HighsStatus clearSolver();

  /**
   * Methods for model input
   */

  /**
   * Every model loading module eventually uses
   * passModel(HighsModel model) to communicate the model to HiGHS.
   */

  /**
   * @brief Pass a HighsModel instance to Highs
   */
  HIGHS_EXPORT HighsStatus passModel(HighsModel model);

  /**
   * @brief Pass a HighsLp instance to Highs
   */
  HIGHS_EXPORT HighsStatus passModel(HighsLp lp);

  /**
   * @brief Pass a QP (possibly with integrality data) via pointers to vectors
   * of data
   */
  HIGHS_EXPORT HighsStatus passModel(
      const HighsInt num_col, const HighsInt num_row, const HighsInt num_nz,
      const HighsInt q_num_nz, const HighsInt a_format, const HighsInt q_format,
      const HighsInt sense, const double offset, const double* col_cost,
      const double* col_lower, const double* col_upper, const double* row_lower,
      const double* row_upper, const HighsInt* a_start, const HighsInt* a_index,
      const double* a_value, const HighsInt* q_start, const HighsInt* q_index,
      const double* q_value, const HighsInt* integrality = nullptr);

  /**
   * @brief Pass an LP (possibly with integrality data) via pointers to vectors
   * of data
   */
  HIGHS_EXPORT HighsStatus passModel(const HighsInt num_col, const HighsInt num_row,
                        const HighsInt num_nz, const HighsInt a_format,
                        const HighsInt sense, const double offset,
                        const double* col_cost, const double* col_lower,
                        const double* col_upper, const double* row_lower,
                        const double* row_upper, const HighsInt* a_start,
                        const HighsInt* a_index, const double* a_value,
                        const HighsInt* integrality = nullptr);

  /**
   * @brief Pass a HighsHessian instance for the incumbent model
   */
  HIGHS_EXPORT HighsStatus passHessian(HighsHessian hessian_);

  /**
   * @brief Pass the Hessian for the incumbent model via pointers to vectors of
   * data
   */
  HIGHS_EXPORT HighsStatus passHessian(const HighsInt dim, const HighsInt num_nz,
                          const HighsInt format, const HighsInt* start,
                          const HighsInt* index, const double* value);
  /**
   * @brief Pass a column name to the incumbent model
   */
  HIGHS_EXPORT HighsStatus passColName(const HighsInt col, const std::string& name);

  /**
   * @brief Pass a row name to the incumbent model
   */
  HIGHS_EXPORT HighsStatus passRowName(const HighsInt row, const std::string& name);

  /**
   * @brief Read in a model
   */
  HIGHS_EXPORT HighsStatus readModel(const std::string& filename);

  /**
   * @brief Read in a basis
   */
  HIGHS_EXPORT HighsStatus readBasis(const std::string& filename);

  /**
   * @brief Presolve the incumbent model
   */
  HIGHS_EXPORT HighsStatus presolve();

  /**
   * @brief Solve the incumbent model according to the specified options
   */
  HIGHS_EXPORT HighsStatus run();

  /**
   * @brief Postsolve the incumbent model using a solution
   */
  HIGHS_EXPORT HighsStatus postsolve(const HighsSolution& solution);

  /**
   * @brief Postsolve the incumbent model using a solution and basis
   */
  HIGHS_EXPORT HighsStatus postsolve(const HighsSolution& solution, const HighsBasis& basis);

  /**
   * @brief Write the current solution to a file in a given style
   */
  HIGHS_EXPORT HighsStatus writeSolution(const std::string& filename,
                            const HighsInt style = kSolutionStyleRaw);

  /**
   * @brief Read a HiGHS solution file in a given style
   */
  HIGHS_EXPORT HighsStatus readSolution(const std::string& filename,
                           const HighsInt style = kSolutionStyleRaw);

  /**
   * @brief Assess the validity, integrality and feasibility of the
   * current primal solution. Of value after calling
   * Highs::readSolution
   */
  HIGHS_EXPORT HighsStatus assessPrimalSolution(bool& valid, bool& integral,
                                   bool& feasible) const;

  /**
   * Methods for HiGHS option input/output
   */

  /**
   * @brief Set an option to the bool/HighsInt/double/string value if it's
   * legal and, for bool/HighsInt/double, only if it's of the correct type
   */

  HIGHS_EXPORT HighsStatus setOptionValue(const std::string& option, const bool value);

  HIGHS_EXPORT HighsStatus setOptionValue(const std::string& option, const HighsInt value);

#ifdef HIGHSINT64
  HighsStatus setOptionValue(const std::string& option, const int value) {
    return setOptionValue(option, HighsInt{value});
  }
#endif

  HIGHS_EXPORT HighsStatus setOptionValue(const std::string& option, const double value);

  HIGHS_EXPORT HighsStatus setOptionValue(const std::string& option,
                             const std::string& value);

  HIGHS_EXPORT HighsStatus setOptionValue(const std::string& option, const char* value);

  /**
   * @brief Read option values from a file
   */
  HIGHS_EXPORT HighsStatus readOptions(const std::string& filename);

  /**
   * @brief Pass a HighsOptions instance to Highs
   */
  HIGHS_EXPORT HighsStatus passOptions(const HighsOptions& options);

  /**
   * @brief Get a const reference to the internal option values
   */
  const HighsOptions& getOptions() const { return options_; }

  /**
   * @brief Gets an option value as bool/HighsInt/double/string and, for
   * bool/int/double, only if it's of the correct type.
   *
   * NB Deprecate in v2.0, in order to replace with more general
   * get*OptionValues
   */
  HighsStatus getOptionValue(const std::string& option, bool& value) const {
    return this->getBoolOptionValues(option, &value);
  }

  HighsStatus getOptionValue(const std::string& option, HighsInt& value) const {
    return this->getIntOptionValues(option, &value);
  }

  HighsStatus getOptionValue(const std::string& option, double& value) const {
    return this->getDoubleOptionValues(option, &value);
  }

  HighsStatus getOptionValue(const std::string& option,
                             std::string& value) const {
    return this->getStringOptionValues(option, &value);
  }

  /**
   * @brief Get the type expected by an option
   */
  HighsStatus getOptionType(const std::string& option,
                            HighsOptionType& type) const {
    return this->getOptionType(option, &type);
  }

  /**
   * @brief Reset the options to the default values
   */
  HIGHS_EXPORT HighsStatus resetOptions();

  /**
   * @brief Write (deviations from default values of) the options to a
   * file, with the extension ".html" producing HTML, otherwise using
   * the standard format used to read options from a file.
   */
  HIGHS_EXPORT HighsStatus writeOptions(const std::string& filename,  //!< The filename
                           const bool report_only_deviations = false) const;

  /**
   * @brief Returns the number of user-settable options
   */
  HighsInt getNumOptions() const {
    return this->options_.num_user_settable_options_;
  }

  /**
   * @brief Get the number of user-settable options
   */
  HIGHS_EXPORT HighsStatus getOptionName(const HighsInt index, std::string* name) const;

  /**
   * @brief Get the type of an option
   */
  HIGHS_EXPORT HighsStatus getOptionType(const std::string& option,
                            HighsOptionType* type) const;

  /**
   * @brief Get the current and default values of a bool option
   */
  HIGHS_EXPORT HighsStatus getBoolOptionValues(const std::string& option,
                                  bool* current_value = nullptr,
                                  bool* default_value = nullptr) const;

  /**
   * @brief Get the current, min, max and default values of an int option
   */
  HIGHS_EXPORT HighsStatus getIntOptionValues(const std::string& option,
                                 HighsInt* current_value = nullptr,
                                 HighsInt* min_value = nullptr,
                                 HighsInt* max_value = nullptr,
                                 HighsInt* default_value = nullptr) const;

  /**
   * @brief Get the current, min, max and default values of a double option
   */
  HIGHS_EXPORT HighsStatus getDoubleOptionValues(const std::string& option,
                                    double* current_value = nullptr,
                                    double* min_value = nullptr,
                                    double* max_value = nullptr,
                                    double* default_value = nullptr) const;

  /**
   * @brief Get the current and default values of a string option
   */
  HIGHS_EXPORT HighsStatus getStringOptionValues(const std::string& option,
                                    std::string* current_value = nullptr,
                                    std::string* default_value = nullptr) const;

  /**
   * @brief Get a const reference to the internal info values
   * type.
   */
  const HighsInfo& getInfo() const { return info_; }

  /**
   * @brief Get an info value as HighsInt/int64_t/double, and only if
   * it's of the correct type.
   */

  HIGHS_EXPORT HighsStatus getInfoValue(const std::string& info, HighsInt& value) const;

#ifndef HIGHSINT64
  HIGHS_EXPORT HighsStatus getInfoValue(const std::string& info, int64_t& value) const;
#endif

  HIGHS_EXPORT HighsStatus getInfoValue(const std::string& info, double& value) const;

  HIGHS_EXPORT HighsStatus getInfoType(const std::string& info, HighsInfoType& type) const;

  /**
   * @brief Write info values to a file, with the extension ".html"
   * producing HTML, otherwise using the standard format used to read
   * options from a file.
   */
  HIGHS_EXPORT HighsStatus writeInfo(const std::string& filename = "") const;

  /**
   * @brief Get the value of infinity used by HiGHS
   */
  double getInfinity() { return kHighsInf; }

  /**
   * @brief Get the size of HighsInt
   */
  HighsInt getSizeofHighsInt() {
    return sizeof(options_.num_user_settable_options_);
  }

  /**
   * @brief Get the run time of HiGHS
   */
  double getRunTime() { return timer_.readRunHighsClock(); }

  /**
   * Methods for model output
   */

  /**
   * @brief Return a const reference to the presolved HighsLp instance in HiGHS
   */
  const HighsLp& getPresolvedLp() const { return presolved_model_.lp_; }

  /**
   * @brief Return a const reference to the presolved HighsModel instance in
   * HiGHS
   */
  const HighsModel& getPresolvedModel() const { return presolved_model_; }

  /**
   * @brief Return a const reference to the logging data for presolve
   */
  const HighsPresolveLog& getPresolveLog() const { return presolve_log_; }

  /**
   * @brief Return a const pointer to the original column indices for
   * the presolved model
   */
  const HighsInt* getPresolveOrigColsIndex() const {
    return presolve_.data_.postSolveStack.getOrigColsIndex();
  }

  /**
   * @brief Return a const pointer to the original row indices for the
   * presolved model
   */
  const HighsInt* getPresolveOrigRowsIndex() const {
    return presolve_.data_.postSolveStack.getOrigRowsIndex();
  }

  /**
   * @brief Return a const reference to the incumbent LP
   */
  const HighsLp& getLp() const { return model_.lp_; }

  /**
   * @brief Return a const reference to the incumbent model
   */
  const HighsModel& getModel() const { return model_; }

  /**
   * @brief Return a const reference to the internal HighsSolution instance
   */
  const HighsSolution& getSolution() const { return solution_; }

  /**
   * @brief Zero all clocks in the internal HighsTimer instance
   */
  void zeroAllClocks() { timer_.zeroAllClocks(); };

  /**
   * @brief Return a const reference to the internal HighsSolution instance
   */
  const std::vector<HighsObjectiveSolution>& getSavedMipSolutions() const {
    return saved_objective_and_solution_;
  }

  /**
   * @brief Return a const reference to the internal ICrash info instance
   */
  const ICrashInfo& getICrashInfo() const { return icrash_info_; };

  /**
   * @brief Return a const reference to the internal HighsBasis instance
   */
  const HighsBasis& getBasis() const { return basis_; }

  /**
   * @brief Return the status for the incumbent model.
   */
  const HighsModelStatus& getModelStatus() const { return model_status_; }

  /**
   * @brief Returns the current model's presolve status
   */
  const HighsPresolveStatus& getModelPresolveStatus() const {
    return model_presolve_status_;
  }

  /**
   * @brief Indicate whether a dual unbounded ray exists, and gets
   * it if it does and dual_ray is not nullptr
   */
  HIGHS_EXPORT HighsStatus getDualRay(bool& has_dual_ray, double* dual_ray_value = nullptr);

  /**
   * @brief Indicate whether a dual unbounded ray exists, and gets
   * it if it does
   */
  HIGHS_EXPORT HighsStatus getDualRaySparse(bool& has_dual_ray, HVector& row_ep_buffer);

  /**
   * @brief Indicate whether a primal unbounded ray exists, and gets
   * it if it does and primal_ray is not nullptr
   */
  HIGHS_EXPORT HighsStatus getPrimalRay(bool& has_primal_ray,
                           double* primal_ray_value = nullptr);

  /**
   * @brief Get the ranging information for the current LP
   */
  HIGHS_EXPORT HighsStatus getRanging(HighsRanging& ranging);

  /**
   * @brief Get the ill-conditioning information for the current basis
   */
  HIGHS_EXPORT HighsStatus getIllConditioning(HighsIllConditioning& ill_conditioning,
                                 const bool constraint,
                                 const HighsInt method = 0,
                                 const double ill_conditioning_bound = 1e-4);

  /**
   * @brief Get the current model objective value
   */
  double getObjectiveValue() const { return info_.objective_function_value; }

  /**
   * Methods for operations with the invertible representation of the
   * current basis matrix
   */

  /**
   * @brief Returns true if an invertible representation of the
   * current basis matrix is available
   */
  HIGHS_EXPORT bool hasInvert() const;

  /**
   * @brief Gets the basic variables in the order corresponding to
   * calls to getBasisInverseRow, getBasisInverseCol, getBasisSolve,
   * getBasisTransposeSolve, getReducedRow and
   * getReducedColumn. Non-negative entries are indices of columns,
   * and negative entries are -(row_index+1).
   */
  HIGHS_EXPORT HighsStatus getBasicVariables(HighsInt* basic_variables);

  /**
   * @brief Form a row of \f$B^{-1}\f$ for basis matrix \f$B\f$,
   * returning the indices of the nonzeros unless row_num_nz is
   * nullptr
   */
  HIGHS_EXPORT HighsStatus getBasisInverseRow(const HighsInt row, double* row_vector,
                                 HighsInt* row_num_nz = nullptr,
                                 HighsInt* row_indices = nullptr);

  /**
   * @brief Form a column of \f$B^{-1}\f$ for basis matrix \f$B\f$,
   * returning the indices of the nonzeros unless col_num_nz is
   * nullptr
   */
  HIGHS_EXPORT HighsStatus getBasisInverseCol(const HighsInt col, double* col_vector,
                                 HighsInt* col_num_nz = nullptr,
                                 HighsInt* col_indices = nullptr);

  /**
   * @brief Form \f$\mathbf{x}=B^{-1}\mathbf{b}\f$ for a given vector
   * \f$\mathbf{b}\f$, returning the indices of the nonzeros unless
   * solution_num_nz is nullptr
   */
  HIGHS_EXPORT HighsStatus getBasisSolve(const double* rhs, double* solution_vector,
                            HighsInt* solution_num_nz = nullptr,
                            HighsInt* solution_indices = nullptr);

  /**
   * @brief Form \f$\mathbf{x}=B^{-T}\mathbf{b}\f$ for a given vector
   * \f$\mathbf{b}\f$, returning the indices of the nonzeros unless
   * solution_num_nz is nullptr
   */
  HIGHS_EXPORT HighsStatus getBasisTransposeSolve(const double* rhs, double* solution_vector,
                                     HighsInt* solution_num_nz = nullptr,
                                     HighsInt* solution_indices = nullptr);

  /**
   * @brief Form a row of \f$B^{-1}A\f$, returning the indices of the
   * nonzeros unless row_num_nz is nullptr, computing the row using
   * pass_basis_inverse_row_vector unless it is nullptr
   */
  HIGHS_EXPORT HighsStatus getReducedRow(
      const HighsInt row, double* row_vector, HighsInt* row_num_nz = nullptr,
      HighsInt* row_indices = nullptr,
      const double* pass_basis_inverse_row_vector = nullptr);

  /**
   * @brief Form a column of \f$B^{-1}A\f$, returning the indices of
   * the nonzeros unless col_num_nz is nullptr
   */
  HIGHS_EXPORT HighsStatus getReducedColumn(const HighsInt col, double* col_vector,
                               HighsInt* col_num_nz = nullptr,
                               HighsInt* col_indices = nullptr);

  /**
   * @brief Get the number of columns in the incumbent model
   */
  HighsInt getNumCol() const { return model_.lp_.num_col_; }

  /**
   * @brief Get the number of rows in the incumbent model
   */
  HighsInt getNumRow() const { return model_.lp_.num_row_; }

  /**
   * @brief Get the number of (constraint matrix) nonzeros in the incumbent
   * model
   */
  HighsInt getNumNz() const { return model_.lp_.a_matrix_.numNz(); }

  /**
   * @brief Get the number of Hessian matrix nonzeros in the incumbent model
   */
  HighsInt getHessianNumNz() const { return model_.hessian_.numNz(); }

  /**
   * @brief Get the objective sense of the incumbent model
   */
  HIGHS_EXPORT HighsStatus getObjectiveSense(ObjSense& sense) const;

  /**
   * @brief Get the objective offset of the incumbent model
   */
  HIGHS_EXPORT HighsStatus getObjectiveOffset(double& offset) const;

  /**
   * @brief Get multiple columns from the model given by an interval [from_col,
   * to_col]
   */
  HIGHS_EXPORT HighsStatus getCols(
      const HighsInt
          from_col,  //!< The index of the first column to get from the model
      const HighsInt
          to_col,  //!< The index of the last column to get from the model
      HighsInt& num_col,  //!< Number of columns got from the model
      double* cost,       //!< Array of size num_col with costs
      double* lower,      //!< Array of size num_col with lower bounds
      double* upper,      //!< Array of size num_col with upper bounds
      HighsInt& num_nz,   //!< Number of nonzeros got from the model
      HighsInt*
          start,  //!< Array of size num_col with start indices of the columns
      HighsInt*
          index,     //!< Array of size num_nz with row indices for the columns
      double* value  //!< Array of size num_nz with row values for the columns
  );

  /**
   * @brief Get multiple columns from the model given by a set
   */
  HIGHS_EXPORT HighsStatus getCols(
      const HighsInt num_set_entries,  //!< The number of indices in the set
      const HighsInt* set,  //!< Array of size num_set_entries with indices of
                            //!< columns to get
      HighsInt& num_col,    //!< Number of columns got from the model
      double* cost,         //!< Array of size num_col with costs
      double* lower,        //!< Array of size num_col with lower bounds
      double* upper,        //!< Array of size num_col with upper bounds
      HighsInt& num_nz,     //!< Number of nonzeros got from the model
      HighsInt*
          start,  //!< Array of size num_col with start indices of the columns
      HighsInt*
          index,     //!< Array of size num_nz with row indices for the columns
      double* value  //!< Array of size num_nz with row values for the columns
  );

  /**
   * @brief Get multiple columns from the model given by a mask
   */
  HIGHS_EXPORT HighsStatus getCols(
      const HighsInt* mask,  //!< Full length array with 1 => get; 0 => not
      HighsInt& num_col,     //!< Number of columns got from the model
      double* cost,          //!< Array of size num_col with cost
      double* lower,         //!< Array of size num_col with lower bounds
      double* upper,         //!< Array of size num_col with upper bounds
      HighsInt& num_nz,      //!< Number of nonzeros got from the model
      HighsInt*
          start,  //!<  Array of size num_col with start indices of the columns
      HighsInt*
          index,     //!<  Array of size num_nz with row indices for the columns
      double* value  //!<  Array of size num_nz with row values for the columns
  );

  /**
   * @brief Get a column name from the incumbent model
   */
  HIGHS_EXPORT HighsStatus getColName(const HighsInt col, std::string& name) const;

  /**
   * @brief Get column index corresponding to name
   */
  HIGHS_EXPORT HighsStatus getColByName(const std::string& name, HighsInt& col);

  /**
   * @brief Get a column integrality from the incumbent model
   */
  HIGHS_EXPORT HighsStatus getColIntegrality(const HighsInt col,
                                HighsVarType& integrality) const;

  /**
   * @brief Get multiple rows from the model given by an interval [from_row,
   * to_row]
   */
  HIGHS_EXPORT HighsStatus getRows(
      const HighsInt
          from_row,  //!< The index of the first row to get from the model
      const HighsInt
          to_row,         //!< The index of the last row to get from the model
      HighsInt& num_row,  //!< Number of rows got from the model
      double* lower,      //!< Array of size num_row with lower bounds
      double* upper,      //!< Array of size num_row with upper bounds
      HighsInt& num_nz,   //!< Number of nonzeros got from the model
      HighsInt*
          start,  //!< Array of size num_row with start indices of the rows
      HighsInt*
          index,     //!< Array of size num_nz with column indices for the rows
      double* value  //!< Array of size num_nz with column values for the rows
  );

  /**
   * @brief Get multiple rows from the model given by a set
   */
  HIGHS_EXPORT HighsStatus getRows(
      const HighsInt num_set_entries,  //!< The number of indices in the set
      const HighsInt*
          set,  //!< Array of size num_set_entries with indices of rows to get
      HighsInt& num_row,  //!< Number of rows got from the model
      double* lower,      //!< Array of size num_row with lower bounds
      double* upper,      //!< Array of size num_row with upper bounds
      HighsInt& num_nz,   //!< Number of nonzeros got from the model
      HighsInt*
          start,  //!< Array of size num_row with start indices of the rows
      HighsInt*
          index,     //!< Array of size num_nz with column indices for the rows
      double* value  //!< Array of size num_nz with column values for the rows
  );

  /**
   * @brief Get multiple rows from the model given by a mask
   */
  HIGHS_EXPORT HighsStatus getRows(
      const HighsInt* mask,  //!< Full length array with 1 => get; 0 => not
      HighsInt& num_row,     //!< Number of rows got from the model
      double* lower,         //!< Array of size num_row with lower bounds
      double* upper,         //!< Array of size num_row with upper bounds
      HighsInt& num_nz,      //!< Number of nonzeros got from the model
      HighsInt*
          start,  //!< Array of size num_row with start indices of the rows
      HighsInt*
          index,     //!< Array of size num_nz with column indices for the rows
      double* value  //!< Array of size num_nz with column values for the rows
  );

  /**
   * @brief Get a row name from the incumbent model
   */
  HIGHS_EXPORT HighsStatus getRowName(const HighsInt row, std::string& name) const;

  /**
   * @brief Get row index corresponding to name
   */
  HIGHS_EXPORT HighsStatus getRowByName(const std::string& name, HighsInt& row);

  /**
   * @brief Get a matrix coefficient
   */
  HIGHS_EXPORT HighsStatus getCoeff(const HighsInt row, const HighsInt col, double& value);

  /**
   * @brief Write out the incumbent model to a file
   */
  HIGHS_EXPORT HighsStatus writeModel(const std::string& filename = "");

  /**
   * @brief Write out the incumbent presolved model to a file
   */
  HIGHS_EXPORT HighsStatus writePresolvedModel(const std::string& filename = "");

  /**
   * @brief Write out the given model to a file
   */
  HIGHS_EXPORT HighsStatus writeLocalModel(HighsModel& model,
                              const std::string& filename = "");

  /**
   * @brief Write out the internal HighsBasis instance to a file
   */
  HIGHS_EXPORT HighsStatus writeBasis(const std::string& filename = "");

  /**
   * Methods for incumbent model modification
   */

  /**
   * @brief Change the objective sense of the incumbent model
   */
  HIGHS_EXPORT HighsStatus changeObjectiveSense(const ObjSense sense);

  /**
   * @brief Change the objective offset of the incumbent model
   */
  HIGHS_EXPORT HighsStatus changeObjectiveOffset(const double offset);

  /**
   * @brief Change the integrality of a column
   */
  HIGHS_EXPORT HighsStatus changeColIntegrality(const HighsInt col,
                                   const HighsVarType integrality);

  /**
   * @brief Change the integrality of multiple columns given by an
   * interval [from_col, to_col]
   */
  HIGHS_EXPORT HighsStatus changeColsIntegrality(const HighsInt from_col,
                                    const HighsInt to_col,
                                    const HighsVarType* integrality);

  /**
   * @brief Change the integrality of multiple columns given by a set of indices
   */
  HIGHS_EXPORT HighsStatus changeColsIntegrality(const HighsInt num_set_entries,
                                    const HighsInt* set,
                                    const HighsVarType* integrality);

  /**
   * @brief Change the integrality of multiple columns given by a mask
   * (full length array with 1 => change; 0 => not)
   */
  HIGHS_EXPORT HighsStatus changeColsIntegrality(const HighsInt* mask,
                                    const HighsVarType* integrality);

  /**
   * @brief Clear the integrality of all columns
   */
  HighsStatus clearIntegrality() {
    this->model_.lp_.integrality_.clear();
    return HighsStatus::kOk;
  }

  /**
   * @brief Change the cost of a column
   */
  HIGHS_EXPORT HighsStatus changeColCost(const HighsInt col, const double cost);

  /**
   * @brief Change the cost of multiple columns given by an interval [from_col,
   * to_col]
   */
  HIGHS_EXPORT HighsStatus changeColsCost(const HighsInt from_col, const HighsInt to_col,
                             const double* cost);

  /**
   * @brief Change the cost of multiple columns given by a set of indices
   */
  HIGHS_EXPORT HighsStatus changeColsCost(const HighsInt num_set_entries,
                             const HighsInt* set, const double* cost);

  /**
   * @brief Change the cost of multiple columns given by a mask
   * (full length array with 1 => change; 0 => not)
   */
  HIGHS_EXPORT HighsStatus changeColsCost(const HighsInt* mask, const double* cost);

  /**
   * @brief Change the bounds of a column
   */
  HIGHS_EXPORT HighsStatus changeColBounds(const HighsInt col, const double lower,
                              const double upper);

  /**
   * @brief Change the bounds of multiple columns given by an interval
   * [from_col, to_col]
   */
  HIGHS_EXPORT HighsStatus changeColsBounds(const HighsInt from_col, const HighsInt to_col,
                               const double* lower, const double* upper);

  /**
   * @brief Change the bounds of multiple columns given by a set of indices
   */
  HIGHS_EXPORT HighsStatus changeColsBounds(const HighsInt num_set_entries,
                               const HighsInt* set, const double* lower,
                               const double* upper);

  /**
   * @brief Change the cost of multiple columns given by a mask (full
   * length array with 1 => change; 0 => not)
   */
  HIGHS_EXPORT HighsStatus changeColsBounds(const HighsInt* mask, const double* lower,
                               const double* upper);

  /**
   * @brief Change the bounds of a row
   */
  HIGHS_EXPORT HighsStatus changeRowBounds(const HighsInt row, const double lower,
                              const double upper);

  /**
   * @brief Change the bounds of multiple rows given by an interval [from_row,
   * to_row]
   */
  HIGHS_EXPORT HighsStatus changeRowsBounds(const HighsInt from_row, const HighsInt to_row,
                               const double* lower, const double* upper);

  /**
   * @brief Change the bounds of multiple rows given by a set of indices
   */
  HIGHS_EXPORT HighsStatus changeRowsBounds(const HighsInt num_set_entries,
                               const HighsInt* set, const double* lower,
                               const double* upper);

  /**
   * @brief Change the cost of multiple rows given by a mask (full
   * length array with 1 => change; 0 => not)
   */
  HIGHS_EXPORT HighsStatus changeRowsBounds(const HighsInt* mask, const double* lower,
                               const double* upper);

  /**
   * @brief Change a matrix coefficient
   */
  HIGHS_EXPORT HighsStatus changeCoeff(const HighsInt row, const HighsInt col,
                          const double value);
  /**
   * @brief Sets the constraint matrix format of the incumbent model
   */
  HighsStatus setMatrixFormat(const MatrixFormat desired_format) {
    this->model_.lp_.setFormat(desired_format);
    return HighsStatus::kOk;
  }

  /**
   * @brief Adds a variable to the incumbent model, without the matrix
   * coefficients if num_new_nz = 0, in which case indices and values
   * arrays can be nullptr
   */
  HIGHS_EXPORT HighsStatus addCol(const double cost, const double lower, const double upper,
                     const HighsInt num_new_nz, const HighsInt* indices,
                     const double* values);

  /**
   * @brief Adds multiple columns to the incumbent model, without the matrix
   * coefficients if num_new_nz = 0, in which case column-wise starts,
   * indices and values arrays can be nullptr
   */
  HIGHS_EXPORT HighsStatus addCols(const HighsInt num_new_col, const double* cost,
                      const double* lower, const double* upper,
                      const HighsInt num_new_nz, const HighsInt* starts,
                      const HighsInt* indices, const double* values);

  /**
   * @brief Adds a variable to the incumbent model, without the cost or matrix
   * coefficients
   */
  HighsStatus addVar(const double lower = 0, const double upper = kHighsInf) {
    return this->addVars(1, &lower, &upper);
  }

  /**
   * @brief Adds multiple variables to the incumbent model, without the costs or
   * matrix coefficients
   */
  HIGHS_EXPORT HighsStatus addVars(const HighsInt num_new_var, const double* lower,
                      const double* upper);

  /**
   * @brief Add a row to the incumbent model, without the matrix coefficients if
   * num_new_nz = 0, in which case indices and values arrays can be
   * nullptr
   */
  HIGHS_EXPORT HighsStatus addRow(const double lower, const double upper,
                     const HighsInt num_new_nz, const HighsInt* indices,
                     const double* values);

  /**
   * @brief Adds multiple rows to the incumbent model, without the matrix
   * coefficients if num_new_nz = 0, in which case row-wise starts,
   * indices and values arrays can be nullptr
   */
  HIGHS_EXPORT HighsStatus addRows(const HighsInt num_new_row, const double* lower,
                      const double* upper, const HighsInt num_new_nz,
                      const HighsInt* starts, const HighsInt* indices,
                      const double* values);

  /**
   * @brief Delete multiple columns from the incumbent model given by an
   * interval [from_col, to_col]
   */
  HIGHS_EXPORT HighsStatus deleteCols(const HighsInt from_col, const HighsInt to_col);

  /**
   * @brief Delete multiple columns from the incumbent model given by a set
   */
  HIGHS_EXPORT HighsStatus deleteCols(const HighsInt num_set_entries, const HighsInt* set);

  /**
   * @brief Delete multiple columns from the incumbent model given by
   * a mask (full length array with 1 => delete; 0 => keep). New index
   * of any column kept is returned in place of the value 0.  For
   * deleted columns, a value of -1 is returned.
   */
  HIGHS_EXPORT HighsStatus deleteCols(HighsInt* mask);

  /**
   * @brief Delete multiple variables from the incumbent model given by an
   * interval [from_var, to_var]
   */
  HighsStatus deleteVars(const HighsInt from_var, const HighsInt to_var) {
    return deleteCols(from_var, to_var);
  }

  /**
   * @brief Delete multiple variables from the incumbent model given by a set
   */
  HighsStatus deleteVars(const HighsInt num_set_entries, const HighsInt* set) {
    return deleteCols(num_set_entries, set);
  }

  /**
   * @brief Delete multiple variables from the incumbent model given
   * by a mask (full length array with 1 => delete; 0 => keep). New
   * index of any variable not deleted is returned in place of the
   * value 0. For deleted variables, a value of -1 is returned.
   */
  HighsStatus deleteVars(HighsInt* mask) { return deleteCols(mask); }

  /**
   * @brief Delete multiple rows from the incumbent model given by an interval
   * [from_row, to_row]
   */
  HIGHS_EXPORT HighsStatus deleteRows(const HighsInt from_row, const HighsInt to_row);

  /**
   * @brief Delete multiple rows from the incumbent model given by a set
   */
  HIGHS_EXPORT HighsStatus deleteRows(const HighsInt num_set_entries, const HighsInt* set);

  /**
   * @brief Delete multiple rows from the incumbent model given by a
   * mask (full length array with 1 => delete; 0 => keep). New index
   * of any row not deleted is returned in place of the value 0. For
   * deleted rows, a value of -1 is returned.
   */
  HIGHS_EXPORT HighsStatus deleteRows(HighsInt* mask);

  /**
   * @brief Scale a matrix column (and cost) by a constant - flipping bounds if
   * the constant is negative
   */
  HIGHS_EXPORT HighsStatus scaleCol(const HighsInt col, const double scale_value);

  /**
   * @brief Scale a matrix row by a constant - flipping bounds if the constant
   * is negative
   */
  HIGHS_EXPORT HighsStatus scaleRow(const HighsInt row, const double scale_value);

  /**
   * Other methods for specialist applications
   */

  /**
   * Methods for setting basis_ and solution_
   */

  /**
   * @brief Pass a HighsSolution instance to set the internal
   * HighsSolution instance. If any of col_value, col_dual and
   * row_dual is not set, the internal HighsSolution instance is not
   * updated
   */
  HIGHS_EXPORT HighsStatus setSolution(const HighsSolution& solution);

  /**
   * @brief Set the callback method to use for HiGHS
   */
  HIGHS_EXPORT HighsStatus setCallback(HighsCallbackFunctionType user_callback,
                          void* user_callback_data = nullptr);
  HIGHS_EXPORT HighsStatus setCallback(HighsCCallbackType c_callback,
                          void* user_callback_data = nullptr);

  /**
   * @brief Start callback of given type
   */
  HIGHS_EXPORT HighsStatus startCallback(const int callback_type);
  HIGHS_EXPORT HighsStatus startCallback(const HighsCallbackType callback_type);

  /**
   * @brief Stop callback of given type
   */
  HIGHS_EXPORT HighsStatus stopCallback(const int callback_type);
  HIGHS_EXPORT HighsStatus stopCallback(const HighsCallbackType callback_type);

  /**
   * @brief Use the HighsBasis passed to set the internal HighsBasis
   * instance. The origin string is used to identify the source of the
   * HighsBasis instance.
   */
  HIGHS_EXPORT HighsStatus setBasis(const HighsBasis& basis, const std::string& origin = "");

  /**
   * @brief Clear the internal HighsBasis instance
   */
  HIGHS_EXPORT HighsStatus setBasis();

  /**
   * @brief Run IPX crossover from a given HighsSolution instance and,
   * if successful, set the internal HighsBasis and HighsSolution
   * instance
   */
  HIGHS_EXPORT HighsStatus crossover(const HighsSolution& user_solution);

  /**
   * @brief Open a named log file
   */
  HIGHS_EXPORT HighsStatus openLogFile(const std::string& log_file = "");

  /**
   * @brief Interpret common qualifiers to string values
   */
  HIGHS_EXPORT std::string presolveStatusToString(
      const HighsPresolveStatus presolve_status) const;
  HIGHS_EXPORT std::string modelStatusToString(const HighsModelStatus model_status) const;
  HIGHS_EXPORT std::string solutionStatusToString(const HighsInt solution_status) const;
  HIGHS_EXPORT std::string basisStatusToString(const HighsBasisStatus basis_status) const;
  HIGHS_EXPORT std::string basisValidityToString(const HighsInt basis_validity) const;
  HIGHS_EXPORT std::string presolveRuleTypeToString(const HighsInt presolve_rule) const;

  /**
   * @brief Releases all resources held by the global scheduler instance. It is
   * not thread-safe to call this function while calling run() or presolve() on
   * any other Highs instance in any thread. After this function has terminated
   * it is guaranteed that eventually all previously created scheduler threads
   * will terminate and allocated memory will be released. After this function
   * has returned the option value for the number of threads may be altered to a
   * new value before the next call to run() or presolve(). If the given bool
   * parameter has value true, then the function will not return until all
   * memory is freed, which might be desirable when debugging heap memory but
   * requires the calling thread to wait for all scheduler threads to wake-up
   * which is usually not necessary.
   */
  HIGHS_EXPORT static void resetGlobalScheduler(bool blocking = false);

  // Start of advanced methods for HiGHS MIP solver
  /**
   * @brief Get the hot start basis data from the most recent simplex
   * solve. Advanced method: for HiGHS MIP solver
   */
  const HotStart& getHotStart() const { return ekk_instance_.hot_start_; }

  /**
   * @brief Set up for simplex using the supplied hot start
   * data. Advanced method: for HiGHS MIP solver
   */
  HIGHS_EXPORT HighsStatus setHotStart(const HotStart& hot_start);

  /**
   * @brief Freeze the current internal HighsBasis instance and
   * standard NLA, returning a value to be used to recover this basis
   * and standard NLA at minimal cost. Advanced method: for HiGHS MIP
   * solver
   */
  HIGHS_EXPORT HighsStatus freezeBasis(HighsInt& frozen_basis_id);

  /**
   * @brief Unfreeze a frozen HighsBasis instance and standard NLA (if
   * possible). Advanced method: for HiGHS MIP solver
   */
  HIGHS_EXPORT HighsStatus unfreezeBasis(const HighsInt frozen_basis_id);

  /**
   * @brief Check that all frozen basis data has been
   * cleared. Advanced method: for HiGHS MIP solver
   */
  HighsStatus frozenBasisAllDataClear() {
    return ekk_instance_.frozenBasisAllDataClear();
  }

  /**
   * @Brief Put a copy of the current iterate - basis; invertible
   * representation and dual edge weights - into storage within
   * HSimplexNla. Advanced method: for HiGHS MIP solver
   */
  HIGHS_EXPORT HighsStatus putIterate();

  /**
   * @Brief Get a copy of the iterate stored within HSimplexNla and
   * overwrite the current iterate. Advanced method: for HiGHS MIP
   * solver
   */
  HIGHS_EXPORT HighsStatus getIterate();

  /**
   * @brief Get the dual edge weights (steepest/devex) in the order of
   * the basic indices or nullptr when they are not available.
   */
  const double* getDualEdgeWeights() const {
    return ekk_instance_.status_.has_dual_steepest_edge_weights
               ? ekk_instance_.dual_edge_weight_.data()
               : nullptr;
  }

  /**
   * @brief Gets the internal basic variable index array in the order
   * corresponding to calls to getBasisInverseRow, getBasisInverseCol,
   * getBasisSolve, getBasisTransposeSolve, getReducedRow and getReducedColumn.
   * Entries are indices of columns if in [0,num_col), and entries in [num_col,
   * num_col+num_row) are (num_col+row_index).
   */
  HIGHS_EXPORT const HighsInt* getBasicVariablesArray() const;

  /**
   * @brief Form a row of \f$B^{-1}\f$ for basis matrix \f$B\f$,
   * returning the result in the given HVector buffer which is
   * expected to be setup with dimension num_row. The buffers
   * previous contents will be overwritten.
   */
  HIGHS_EXPORT HighsStatus getBasisInverseRowSparse(const HighsInt row,
                                       HVector& row_ep_buffer);

  // Start of deprecated methods

  std::string compilationDate() const { return "deprecated"; }

  HIGHS_EXPORT HighsStatus setLogCallback(void (*user_log_callback)(HighsLogType,
                                                       const char*, void*),
                             void* user_log_callback_data = nullptr);

  HighsInt getNumCols() const {
    deprecationMessage("getNumCols", "getNumCol");
    return getNumCol();
  }
  HighsInt getNumRows() const {
    deprecationMessage("getNumRows", "getNumRow");
    return getNumRow();
  }
  HighsInt getNumEntries() {
    deprecationMessage("getNumEntries", "getNumNz");
    return getNumNz();
  }

  HIGHS_EXPORT HighsStatus setHighsOptionValue(const std::string& option, const bool value);

  HIGHS_EXPORT HighsStatus setHighsOptionValue(const std::string& option,
                                  const HighsInt value);

#ifdef HIGHSINT64
  HighsStatus setHighsOptionValue(const std::string& option,
                                  const int value  //!< The option value
  ) {
    deprecationMessage("setHighsOptionValue", "setOptionValue");
    return setOptionValue(option, HighsInt{value});
  }
#endif

  HIGHS_EXPORT HighsStatus setHighsOptionValue(const std::string& option,
                                  const double value);

  HIGHS_EXPORT HighsStatus setHighsOptionValue(
      const std::string& option,
      const std::string& value  //!< The option value
  );

  HIGHS_EXPORT HighsStatus setHighsOptionValue(const std::string& option, const char* value);

  HIGHS_EXPORT HighsStatus readHighsOptions(const std::string& filename  //!< The filename
  );

  HIGHS_EXPORT HighsStatus passHighsOptions(const HighsOptions& options  //!< The options
  );

  HIGHS_EXPORT HighsStatus getHighsOptionValue(const std::string& option, bool& value);

  HIGHS_EXPORT HighsStatus getHighsOptionValue(const std::string& option, HighsInt& value);

  HIGHS_EXPORT HighsStatus getHighsOptionValue(const std::string& option, double& value);

  HIGHS_EXPORT HighsStatus getHighsOptionValue(const std::string& option,
                                  std::string& value);

  HIGHS_EXPORT HighsStatus getHighsOptionType(const std::string& option,
                                 HighsOptionType& type  //!< The option type
  );

  HIGHS_EXPORT const HighsOptions& getHighsOptions() const;

  HIGHS_EXPORT HighsStatus resetHighsOptions();

  HIGHS_EXPORT HighsStatus writeHighsOptions(
      const std::string& filename,  //!< The filename
      const bool report_only_non_default_values = true);

  HighsInt getSimplexIterationCount() {
    deprecationMessage("getSimplexIterationCount", "None");
    return info_.simplex_iteration_count;
  }

  HIGHS_EXPORT HighsStatus setHighsLogfile(FILE* logfile = nullptr);

  HIGHS_EXPORT HighsStatus setHighsOutput(FILE* output = nullptr);

  HIGHS_EXPORT const HighsInfo& getHighsInfo() const;

  HIGHS_EXPORT HighsStatus getHighsInfoValue(const std::string& info, HighsInt& value);

  HIGHS_EXPORT HighsStatus getHighsInfoValue(const std::string& info,
                                double& value) const;  //!< The info value

  HIGHS_EXPORT HighsStatus writeHighsInfo(const std::string& filename  //!< The filename
  );

  HIGHS_EXPORT double getHighsInfinity();

  HIGHS_EXPORT double getHighsRunTime();

  HIGHS_EXPORT const HighsModelStatus& getModelStatus(const bool scaled_model) const;

  HIGHS_EXPORT void logHeader();

  HIGHS_EXPORT void deprecationMessage(const std::string& method_name,
                          const std::string& alt_method_name) const;

  // End of deprecated methods
 private:
  HighsSolution solution_;
  HighsBasis basis_;
  ICrashInfo icrash_info_;

  HighsModel model_;
  HighsModel presolved_model_;
  HighsTimer timer_;

  HighsCallback callback_;
  HighsOptions options_;
  HighsInfo info_;
  HighsRanging ranging_;

  std::vector<HighsObjectiveSolution> saved_objective_and_solution_;

  HighsPresolveStatus model_presolve_status_ =
      HighsPresolveStatus::kNotPresolved;
  HighsModelStatus model_status_ = HighsModelStatus::kNotset;

  HEkk ekk_instance_;

  HighsPresolveLog presolve_log_;

  HighsInt max_threads = 0;
  // This is strictly for debugging. It's used to check whether
  // returnFromRun() was called after the previous call to
  // Highs::run() and, assuming that this is always done, it checks
  // whether Highs::run() is called recursively.
  bool called_return_from_run = true;
  HighsInt debug_run_call_num_ = 0;

  bool written_log_header = false;

  void exactResizeModel() {
    this->model_.lp_.exactResize();
    this->model_.hessian_.exactResize();
  }

  HIGHS_EXPORT HighsStatus completeSolutionFromDiscreteAssignment();

  HIGHS_EXPORT HighsStatus callSolveLp(HighsLp& lp, const string message);
  HIGHS_EXPORT HighsStatus callSolveQp();
  HIGHS_EXPORT HighsStatus callSolveMip();
  HIGHS_EXPORT HighsStatus callRunPostsolve(const HighsSolution& solution,
                               const HighsBasis& basis);

  PresolveComponent presolve_;
  HIGHS_EXPORT HighsPresolveStatus runPresolve(const bool force_lp_presolve,
                                  const bool force_presolve = false);
  HIGHS_EXPORT HighsPostsolveStatus runPostsolve();

  HIGHS_EXPORT HighsStatus openWriteFile(const string filename, const string method_name,
                            FILE*& file, HighsFileType& file_type) const;

  HIGHS_EXPORT void reportModel();
  HIGHS_EXPORT void newHighsBasis();
  HIGHS_EXPORT void forceHighsSolutionBasisSize();
  //
  // For cases where there is no solution data for the model, but its
  // status is proved otherwise. Sets the model status, then clears any solution
  // and basis data
  HIGHS_EXPORT void setHighsModelStatusAndClearSolutionAndBasis(
      const HighsModelStatus model_status);
  //
  // Sets model status, basis, solution and info from the
  // highs_model_object
  HIGHS_EXPORT void setBasisValidity();
  //
  // Clears the presolved model and its status
  HIGHS_EXPORT void clearPresolve();
  //
  // Methods to clear solver data for users in Highs class members
  // before (possibly) updating them with data from trying to solve
  // the incumbent model.
  //
  // Invalidates all solver data in Highs class members by calling
  // invalidateModelStatus(), invalidateSolution(), invalidateBasis(),
  // invalidateInfo() and invalidateEkk()
  HIGHS_EXPORT void invalidateUserSolverData();
  //
  // Invalidates the model status, solution_ and info_
  HIGHS_EXPORT void invalidateModelStatusSolutionAndInfo();
  //
  // Sets model status to HighsModelStatus::kNotset
  HIGHS_EXPORT void invalidateModelStatus();
  //
  // Invalidates primal and dual solution
  HIGHS_EXPORT void invalidateSolution();
  //
  // Invalidates basis
  HIGHS_EXPORT void invalidateBasis();
  //
  // Invalidates info_ and resets the values of its members
  HIGHS_EXPORT void invalidateInfo();
  //
  // Invalidates ranging_
  HIGHS_EXPORT void invalidateRanging();

  // Invalidates ekk_instance_
  HIGHS_EXPORT void invalidateEkk();

  HIGHS_EXPORT HighsStatus returnFromWriteSolution(FILE* file,
                                      const HighsStatus return_status);
  HIGHS_EXPORT HighsStatus returnFromRun(const HighsStatus return_status,
                            const bool undo_mods);
  HIGHS_EXPORT HighsStatus returnFromHighs(const HighsStatus return_status);
  HIGHS_EXPORT void reportSolvedLpQpStats();

  HIGHS_EXPORT void underDevelopmentLogMessage(const std::string& method_name);

  // Interface methods
  HIGHS_EXPORT HighsStatus basisForSolution();
  HIGHS_EXPORT HighsStatus addColsInterface(
      HighsInt ext_num_new_col, const double* ext_col_cost,
      const double* ext_col_lower, const double* ext_col_upper,
      HighsInt ext_num_new_nz, const HighsInt* ext_a_start,
      const HighsInt* ext_a_index, const double* ext_a_value);

  HIGHS_EXPORT HighsStatus addRowsInterface(HighsInt ext_num_new_row,
                               const double* ext_row_lower,
                               const double* ext_row_upper,
                               HighsInt ext_num_new_nz,
                               const HighsInt* ext_ar_start,
                               const HighsInt* ext_ar_index,
                               const double* ext_ar_value);

  HIGHS_EXPORT void deleteColsInterface(HighsIndexCollection& index_collection);

  HIGHS_EXPORT void deleteRowsInterface(HighsIndexCollection& index_collection);

  HIGHS_EXPORT void getColsInterface(const HighsIndexCollection& index_collection,
                        HighsInt& num_col, double* col_cost, double* col_lower,
                        double* col_upper, HighsInt& num_nz,
                        HighsInt* col_matrix_start, HighsInt* col_matrix_index,
                        double* col_matrix_value);

  HIGHS_EXPORT void getRowsInterface(const HighsIndexCollection& index_collection,
                        HighsInt& num_row, double* row_lower, double* row_upper,
                        HighsInt& num_nz, HighsInt* row_matrix_start,
                        HighsInt* row_matrix_index, double* row_matrix_value);

  HIGHS_EXPORT void getCoefficientInterface(const HighsInt ext_row, const HighsInt ext_col,
                               double& value);

  HIGHS_EXPORT HighsStatus changeObjectiveSenseInterface(const ObjSense ext_sense);
  HIGHS_EXPORT HighsStatus changeObjectiveOffsetInterface(const double ext_offset);
  HIGHS_EXPORT HighsStatus changeIntegralityInterface(HighsIndexCollection& index_collection,
                                         const HighsVarType* usr_inegrality);
  HIGHS_EXPORT HighsStatus changeCostsInterface(HighsIndexCollection& index_collection,
                                   const double* usr_col_cost);
  HIGHS_EXPORT HighsStatus changeColBoundsInterface(HighsIndexCollection& index_collection,
                                       const double* usr_col_lower,
                                       const double* usr_col_upper);
  HIGHS_EXPORT HighsStatus changeRowBoundsInterface(HighsIndexCollection& index_collection,
                                       const double* usr_row_lower,
                                       const double* usr_row_upper);
  HIGHS_EXPORT void changeCoefficientInterface(const HighsInt ext_row,
                                  const HighsInt ext_col,
                                  const double ext_new_value);
  HIGHS_EXPORT HighsStatus scaleColInterface(const HighsInt col, const double scale_value);
  HIGHS_EXPORT HighsStatus scaleRowInterface(const HighsInt row, const double scale_value);

  HIGHS_EXPORT void setNonbasicStatusInterface(const HighsIndexCollection& index_collection,
                                  const bool columns);
  HIGHS_EXPORT void appendNonbasicColsToBasisInterface(const HighsInt ext_num_new_col);
  HIGHS_EXPORT void appendBasicRowsToBasisInterface(const HighsInt ext_num_new_row);

  HIGHS_EXPORT HighsStatus getBasicVariablesInterface(HighsInt* basic_variables);
  HIGHS_EXPORT HighsStatus basisSolveInterface(const vector<double>& rhs,
                                  double* solution_vector,
                                  HighsInt* solution_num_nz,
                                  HighsInt* solution_indices, bool transpose);

  HIGHS_EXPORT HighsStatus setHotStartInterface(const HotStart& hot_start);

  HIGHS_EXPORT void zeroIterationCounts();

  HIGHS_EXPORT HighsStatus getDualRayInterface(bool& has_dual_ray, double* dual_ray_value);

  HIGHS_EXPORT HighsStatus getPrimalRayInterface(bool& has_primal_ray,
                                    double* primal_ray_value);
  HIGHS_EXPORT HighsStatus getRangingInterface();

  HIGHS_EXPORT bool aFormatOk(const HighsInt num_nz, const HighsInt format);
  HIGHS_EXPORT bool qFormatOk(const HighsInt num_nz, const HighsInt format);
  HIGHS_EXPORT void clearZeroHessian();
  HIGHS_EXPORT HighsStatus checkOptimality(const std::string& solver_type,
                              HighsStatus return_status);
  HIGHS_EXPORT HighsStatus invertRequirementError(std::string method_name);
  HIGHS_EXPORT HighsStatus lpInvertRequirementError(std::string method_name);

  HIGHS_EXPORT HighsStatus handleInfCost();
  HIGHS_EXPORT void restoreInfCost(HighsStatus& return_status);
  HIGHS_EXPORT HighsStatus optionChangeAction();
  HIGHS_EXPORT HighsStatus computeIllConditioning(HighsIllConditioning& ill_conditioning,
                                     const bool constraint,
                                     const HighsInt method,
                                     const double ill_conditioning_bound);
  HIGHS_EXPORT void formIllConditioningLp0(HighsLp& ill_conditioning_lp,
                              std::vector<HighsInt>& basic_var,
                              const bool constraint);
  HIGHS_EXPORT void formIllConditioningLp1(HighsLp& ill_conditioning_lp,
                              std::vector<HighsInt>& basic_var,
                              const bool constraint,
                              const double ill_conditioning_bound);
  HIGHS_EXPORT bool infeasibleBoundsOk();
};

// Start of deprecated methods not in the Highs class

const char* highsCompilationDate();

#endif
