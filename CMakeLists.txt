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

# =========================================================================
# ============================== Armadillo ================================
# =========================================================================
target_include_directories(${APP_NAME} PRIVATE src/libs/armadillo-9.200.5)
# =========================================================================

# =========================================================================
# ============================== SUNDIALS =================================
# =========================================================================
add_subdirectory(src/libs/sundials-4.0.0 "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/sundials")
target_include_directories(${APP_NAME} PRIVATE ${sundials_SOURCE_DIR}/include)
target_link_libraries(${APP_NAME}
                        sundials_cvode_static
                        sundials_sunlinsoldense_static
                        sundials_sunmatrixdense_static
                        sundials_nvecpthreads_static
                        )
# =========================================================================
