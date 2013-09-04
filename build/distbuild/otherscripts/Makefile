LAST_TAG_COMMIT = $(shell git rev-list --tags --max-count=1)
LAST_TAG = $(shell git describe --tags $(LAST_TAG_COMMIT) )
TAG_PREFIX = "latex-tutorial-v"

#VERSION  = $(shell head VERSION)
# OR try to guess directly from the last git tag
#VERSION    = $(shell  git describe --tags $(LAST_TAG_COMMIT) | sed "s/^$(TAG_PREFIX)//")
VERSION = v0.5a
MAJOR      = $(shell echo $(VERSION) | sed "s/^.*\([0-9]*\).*/\1/")
MINOR      = $(shell echo $(VERSION) | sed "s/[0-9]*\.\([0-9]*\).*/\1/")
PATCH      = $(shell echo $(VERSION) | sed "s/[0-9]*\.[0-9]*\.\([0-9]*\).*/\1/")
# total number of commits       
BUILD      = $(shell git log --oneline | wc -l | sed -e "s/[ \t]*//g")

#REVISION   = $(shell git rev-list $(LAST_TAG).. --count)
#ROOTDIR    = $(shell git rev-parse --show-toplevel)
NEXT_MAJOR_VERSION = $(shell expr $(MAJOR) + 1).0.0-b$(BUILD)
NEXT_MINOR_VERSION = $(MAJOR).$(shell expr $(MINOR) + 1).0-b$(BUILD)
NEXT_PATCH_VERSION = $(MAJOR).$(MINOR).$(shell expr $(PATCH) + 1)-b$(BUILD)

dummy:
	@echo VERSION: $(VERSION)
	@echo MAJOR: $(MAJOR)
	@echo MINOR: $(MINOR)
	@echo PATCH: $(PATCH)
	@echo Version: $(MAJOR).$(MINOR).$(PATCH)-$(BUILD)

	@echo NEXT_MAJOR_VERSION: $(NEXT_MAJOR_VERSION)
	@echo NEXT_MINOR_VERSION: $(NEXT_MINOR_VERSION)
	@echo NEXT_PATCH_VERSION: $(NEXT_PATCH_VERSION)
