notrans_dist_man3_MANS = libarithmos.3

if FORCE_MANPAGE_COMPRESSION
install-data-hook:
	-for file in $(notrans_dist_man3_MANS) ;\
	do \
		@MCOMPRESS@ --force -- "$(DESTDIR)$(man3dir)/$$file" ;\
	done
else
install-data-hook:
	-for file in $(notrans_dist_man3_MANS) ;\
	do \
		if expr `@MCOMPRESS@ --stdout -- "$(DESTDIR)$(man3dir)/$$file" | wc -c` '>=' `cat -- "$(DESTDIR)$(man3dir)/$$file" | wc -c` >/dev/null 2>&1 ;\
		then : ;\
		else \
			@MCOMPRESS@ --force -- "$(DESTDIR)$(man3dir)/$$file" ;\
		fi ;\
	done
endif

uninstall-hook:
	-for file in $(notrans_dist_man3_MANS) ;\
	do \
		rm -f  "$(DESTDIR)$(man3dir)"/$${file}.* ;\
	done
