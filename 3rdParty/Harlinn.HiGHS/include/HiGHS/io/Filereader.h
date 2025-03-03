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
/**@file io/Filereader.h
 * @brief
 */
#ifndef IO_FILEREADER_H_
#define IO_FILEREADER_H_

#include "io/HighsIO.h"
#include "lp_data/HighsOptions.h"
#include "model/HighsModel.h"

enum class FilereaderRetcode {
  kOk = 0,
  kFileNotFound = 1,
  kParserError = 2,
  kNotImplemented = 3,
  kTimeout
};

HIGHS_EXPORT void interpretFilereaderRetcode(const HighsLogOptions& log_options,
                                const std::string filename,
                                const FilereaderRetcode code);
HIGHS_EXPORT std::string extractModelName(const std::string filename);

class Filereader {
 public:
  HIGHS_EXPORT virtual FilereaderRetcode readModelFromFile(const HighsOptions& options,
                                              const std::string filename,
                                              HighsModel& model) = 0;
  HIGHS_EXPORT virtual HighsStatus writeModelToFile(const HighsOptions& options,
                                       const std::string filename,
                                       const HighsModel& model) = 0;
  HIGHS_EXPORT static Filereader* getFilereader(const HighsLogOptions& log_options,
                                   const std::string filename);

  virtual ~Filereader(){};
};
#endif
