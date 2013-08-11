LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := DroidSoundFX

MY_FILES := $(wildcard $(LOCAL_PATH)/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/utils/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/effects/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/nativeEffects/*.cpp)
MY_FILES := $(MY_FILES:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES += $(MY_FILES)

# for native audio
LOCAL_LDLIBS    += -lOpenSLES
# for logging
LOCAL_LDLIBS    += -llog
# for native asset manager
#LOCAL_LDLIBS    += -landroid

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)