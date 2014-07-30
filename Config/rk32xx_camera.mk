ifeq ($(strip $(TARGET_BOARD_PLATFORM)), rk3288)
TARGET_OUT=out/target/product/rk3288
#hardware=hardware/rk29/camera/Config 
$(shell cp -rf hardware/rk29/camera/Config/cam_board.xml $(TARGET_OUT)/system/etc/) 
$(shell cp -rf hardware/rk29/camera/Config/libisp_silicomimageisp_api.so $(TARGET_OUT)/obj/) 
$(shell cp -rf hardware/rk29/camera/Config/libisp_silicomimageisp_api.so $(TARGET_OUT)/system/lib/) 
$(shell cp -rf hardware/rk29/camera/Config/../SiliconImage/isi/drv/OV8820/calib/OV8820.xml $(TARGET_OUT)/system/etc/) 
$(shell cp -rf hardware/rk29/camera/Config/../SiliconImage/isi/drv/OV8825/calib/OV8825.xml $(TARGET_OUT)/system/etc/) 
$(shell cp -rf hardware/rk29/camera/Config/../SiliconImage/isi/drv/OV8858/calib/OV8858.xml $(TARGET_OUT)/system/etc/) 
$(shell cp -rf hardware/rk29/camera/Config/../SiliconImage/isi/drv/OV13850/calib/OV13850.xml $(TARGET_OUT)/system/etc/) 
endif

ifeq ($(strip $(TARGET_BOARD_PLATFORM)), rk312x)
$(shell cp -rf hardware/rk29/camera/Config/libisp_silicomimageisp_api.so $(TARGET_OUT)/obj/) 
$(shell cp -rf hardware/rk29/camera/Config/libisp_silicomimageisp_api.so $(TARGET_OUT)/system/lib/) 
endif