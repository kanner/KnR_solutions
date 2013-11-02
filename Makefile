all clean cscope tags help:
	@for i in `find . -maxdepth 1 -type d \! -name "." ! -name ".git"`; do \
		make -C $${i} $@ || exit 1; \
	done
