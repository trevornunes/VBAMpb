# This is an automatically generated makefile.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

include $(MKFILES_ROOT)/qmacros.mk

# QNX Internal Start
EXTRA_SRCVPATH+=$(PROJECT_ROOT)/src
CCFLAGS+=-D_FORTIFY_SOURCE=2 -DLSB_FIRST -D__QNXNTO__ -O3
LIBS+=bps socket png xml2 m SDL12 TouchControlOverlay
EXTRA_INCVPATH+="${workspace_loc:/${ProjName}/3rdparty/inc}" \
	${QNX_TARGET}/usr/include/freetype2 \
	"${workspace_loc:/${ProjName}/src}" \
	"C:\bbndk-2.0.0-beta1\target\qnx6\usr\include\cpp" \
	"C:\bbndk-2.0.0-beta1\target\qnx6\usr\include\cpp\c" \
	${QNX_TARGET}/../target-override/usr/include \
	/usr/include/c++/4.2.2
EXTRA_LIBVPATH+=${QNX_TARGET}/../target-override/${CPUVARDIR}/lib \
	"${workspace_loc:/${ProjName}/3rdparty/libs}" \
	${QNX_TARGET}/../target-override/${CPUVARDIR}/usr/lib

ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

# QNX Internal End

include $(MKFILES_ROOT)/qtargets.mk
OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))
