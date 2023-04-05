HDF version 4.2.15 released on 2020-03-03
===================================================

Information about HDF
---------------------

 The HDF (or HDF4) home page is located here:

    https://support.hdfgroup.org/products/hdf4/

 The most recent version of the software can be obtained from:

    https://support.hdfgroup.org/release4/obtain.html

 The HDF documentation can be found in:

    https://support.hdfgroup.org/release4/doc/index.html


Source Distribution Layout
--------------------------

 The top level of the source code distribution contains the following 
 subdirectories:

   bin    -- Scripts for maintenance.

   config -- Configuration files to be used by configure script.

   hdf    -- The source code for the HDF 'base library', the multi-file 
             annotation interface, the multi-file raster image interface, 
             HDF command line utilities, and a test suite. 
             Please see the README in each directory for further 
             information on each package. 

   java   -- The Java HDF JNI library

   m4     -- Autotools macros and libtool files for building with autotools.

   mfhdf  -- The netCDF(mfhdf) part of the HDF/mfhdf distribution and
             additional HDF utilities, such as hdp, hrepack, hdfimport, etc.

   man    -- An incomplete set of man page(s) for HDF.

   release_notes -- 
             Installation instructions for UNIX and Windows.
             Descriptions of new features and bug fixes in this release.
             Files in this sub-directory can be used as supplemental 
             documentation for HDF. 


Third Party Software Requirements
---------------------------------
  * JPEG distribution release 6b or later.

  * ZLIB 1.1.4(libz.a) or later. 


System Requirements
-------------------
 To build the HDF library from source, you need:

   * C and Fortran compilers. For a list of the supported compilers,
     see release_notes/RELEASE.txt file.


Configuring/Testing/Installing 
------------------------------
 See the file release_notes/INSTALL for instructions on configuring, testing,
 and installing this software on Unix and non-UNIX systems.

