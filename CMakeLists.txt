# ======================= ofxCMake Vers. 0.1 =============
#  PUT THIS FILE INTO YOUR OPENFRAMEWORKS PROJECT FOLDER

# ========================================================
# ===================== CMake Settings ===================
# ========================================================
cmake_minimum_required( VERSION 3.3 )
project( openframeworks )

# ========================================================
# ===================== User Settings ====================
# ========================================================
# ------------------------ OF Path -----------------------
# --- If outside the OF structure, set an absolute OF path
set( OF_DIRECTORY_BY_USER "${CMAKE_CURRENT_LIST_DIR}/openFrameworks-0.10.1" )

# ---------------------- App name  -----------------------
set( APP_NAME mrg_axon_model )

# --------------------- Source Files ---------------------
set( ${APP_NAME}_SOURCE_FILES
        src/MRG_main.cpp
        src/MRG_init.cpp
        src/MRG_ode.cpp
        src/utils.cpp
        src/libs/nvec_ser/nvector_serial.c
        src/libs/nvec_ser/fnvector_serial.c
        src/libs/sundials/sundials_math.c
        src/libs/sundials/sundials_spgmr.c
        src/libs/sundials/sundials_iterative.c
        src/libs/sundials/sundials_dense.c
        src/libs/sundials/sundials_nvector.c
        src/libs/sundials/sundials_sptfqmr.c
        src/libs/sundials/sundials_band.c
        src/libs/sundials/sundials_direct.c
        src/libs/sundials/sundials_spbcgs.c
        src/libs/cvode/cvode_diag.c
        src/libs/cvode/cvode_spbcgs.c
        src/libs/cvode/cvode_io.c
        src/libs/cvode/cvode.c
        src/libs/cvode/cvode_band.c
        src/libs/cvode/cvode_spils.c
        src/libs/cvode/cvode_bbdpre.c
        src/libs/cvode/cvode_spgmr.c
        src/libs/cvode/cvode_sptfqmr.c
        src/libs/cvode/cvode_dense.c
        src/libs/cvode/cvode_bandpre.c
        src/libs/cvode/cvode_direct.c
        src/ofApp.cpp
        )

# ------------------------ AddOns  -----------------------
set( OFX_ADDONS_ACTIVE
#        ofxXmlSettings
#        ofxOsc
#        ofxGui
#        ofxNetwork
#        ofxVectorGraphics
#        ofxThreadedImageLoader
#        ofxAssimpModelLoader
#        ofxKinect
#        ofxOpenCv
#        ofxSvg
#        ofxEmscripten (untested)
        )

# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================

target_include_directories(${APP_NAME} PRIVATE src/libs)
