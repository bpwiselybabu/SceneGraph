ADD_SUBDIRECTORY(Display)
ADD_SUBDIRECTORY(DisplayImage)
ADD_SUBDIRECTORY(DisplayMultiView)

if(NOT _ANDROID_)
  if(HAVE_CVARS)
    include_directories(${CVars_INCLUDE_DIRS})
  endif(HAVE_CVARS)
    ADD_SUBDIRECTORY(DisplayShadowTest)
    ADD_SUBDIRECTORY(ModelPhysics)
    ADD_SUBDIRECTORY(Widgets)
    ADD_SUBDIRECTORY(ModelViewer)

    FIND_PACKAGE( PNG QUIET )
    IF(PNG_FOUND)
      ADD_SUBDIRECTORY(OffscreenRender)
    ENDIF()

endif()
