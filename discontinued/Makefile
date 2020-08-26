SUBDIRS := src/

all: $(SUBDIRS)

clean: 
		rm -f src/*.o bin/*

$(SUBDIRS):
		$(MAKE) -C $@

.PHONY: all $(SUBDIRS)