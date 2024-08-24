
samplesdir = @PSPSDK@/samples

SAMPLES = \
	audio/polyphonic \
	audio/wavegen \
	controller/basic \
	debug/exception \
	debug/kprintf \
	debug/prxdecrypt \
	debug/profiler \
	debug/debugkb \
	debug/sio \
	debug/gdb \
	gprof/basic \
	gprof/custom \
	gu/beginobject \
	gu/blend \
	gu/blit \
	gu/celshading \
	gu/clut \
	gu/common \
	gu/copy \
	gu/cube \
	gu/envmap \
	gu/integerdrawing \
	gu/lights \
	gu/lines \
	gu/logic \
	gu/morph \
	gu/morphskin \
	gu/ortho \
	gu/reflection \
	gu/rendertarget \
	gu/shadowprojection \
	gu/signals \
	gu/skinning \
	gu/speed \
	gu/spharm \
	gu/splinesurface \
	gu/sprite \
	gu/text \
	gu/timing \
	gu/vertex \
	gu/zbufferfog \
	ir/sircs \
	ir/irda \
	kernel/kdumper \
	kernel/loadmodule \
	kernel/threadstatus \
	kernel/cwd \
	kernel/fileio \
	kernel/idstorage \
	kernel/messagebox \
	kernel/registry \
	kernel/regenum \
	kernel/systimer \
	kernel/sysevent \
	mp3 \
	ms/callback \
	nand/dumpipl \
	net/simple \
	net/simple_prx \
	net/resolver \
	net/wlanscan \
	net/wlanscan_elf \
	power \
	prx/prx_loader \
	prx/testprx \
	savedata/utility \
	savedata/decrypt \
	savedata/encrypt \
	template/elf_template \
	template/prx_template \
	template/lib_template \
	template/kprx_template \
	usb/storage \
	utility/gamesharing \
	utility/htmlviewer \
	utility/netconf \
	utility/netdialog \
	utility/msgdialog \
	utility/systemparam \
	utility/osk \
	me/basic \
	wlan \
	exceptions

all:

# Install all of the samples.  Rename any files that end in a .sample extension.
SAMPLES_INSTALL = $(INSTALL_DATA)
install-data-hook:
	$(mkinstalldirs) $(DESTDIR)$(samplesdir)
	@list='$(SAMPLES)'; for s in $$list; do \
	  $(mkinstalldirs) $(DESTDIR)$(samplesdir)/$$s; \
	  for p in $(srcdir)/$$s/*; do \
	    if test -f $$p; then \
	      f="`echo $$p | sed -e 's|^.*/||'`"; \
	      echo " $(SAMPLES_INSTALL) $$p $(DESTDIR)$(samplesdir)/$$s/$$f"; \
	      $(SAMPLES_INSTALL) $$p $(DESTDIR)$(samplesdir)/$$s/$$f; \
	    else :; fi; \
	  done; \
	done
	@for p in `find $(DESTDIR)$(samplesdir) -name *.sample -print `; do \
	  f="`echo $$p | sed -e 's/\.sample$$//'`"; \
	  echo " mv $$p $$f"; \
	  mv $$p $$f;  \
	done

uninstall-hook:
	@list='$(SAMPLES)'; for s in $$list; do \
	  for p in $(DESTDIR)$(samplesdir)/$$s/*; do \
	    if test -f $$p; then \
	      p="`echo $$p | sed -e 's|^.*/||'`"; \
	      echo " rm -f $(DESTDIR)$(samplesdir)/$$s/$$p"; \
	      rm -f $(DESTDIR)$(samplesdir)/$$s/$$p; \
	    else :; fi; \
	  done; \
	done

EXTRA_DIST = $(SAMPLES)
