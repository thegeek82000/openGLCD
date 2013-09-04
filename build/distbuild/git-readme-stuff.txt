Stuff that creates "build" number/information:
====================================================================
git rev-list HEAD -1
git rev-list HEAD -n 1
git log -n 1 --format=%H
(show most recent commit SHA1/rev )

git log -n 1 --format=%ci
(show most recent ISO 8601 date/time commit)

git log -n 1 --format=%aD
(show most recent RFC2822 date/time commit)

git clean
(remove untracked files)

====================================================================
Generate revision info
http://stackoverflow.com/questions/514188/how-would-you-include-the-current-commit-id-in-a-git-projects-files
https://gist.github.com/seanf/880771
====================================================================
Some of this was from:
http://stackoverflow.com/questions/4120001/what-is-the-git-equivalent-for-revision-number

http://cd34.com/blog/programming/using-git-to-generate-an-automatic-version-number/k

====================================================================
git describe "tag"
("tag" is optional)
i.e.
git describe
git describe HEAD
git describe master
git describe tag-name

====================================================================
git log --oneline |wc -l
(gives a number kindof like SVN build number)

====================================================================

git rev-list HEAD |wc -l
(gives a number kindof like SVN build number for HEAD branch)

====================================================================

bap: note: the date needs to be date of the commit not todays date

git_rev ()
{
    d=`date +%Y%m%d`
    c=`git rev-list --full-history --all --abbrev-commit | wc -l | sed -e 's/^ *//'`
    h=`git rev-list --full-history --all --abbrev-commit | head -1`
    echo ${c}:${h}:${d}
}
outputs something like:
2:0f8e14e:20130220

Which is:
commit_count:last_abbrev_commit:date_YYmmdd
====================================================================

fancy stuff for makefile

If you're interested, I managed version numbers automatically from git infos here under the format

<major>.<minor>.<patch>-b<build>

where build is the total number of commits. You'll see the interesting code in the Makefile. Here is the relevant part to access the different part of the version number:

LAST_TAG_COMMIT = $(shell git rev-list --tags --max-count=1)
LAST_TAG = $(shell git describe --tags $(LAST_TAG_COMMIT) )
TAG_PREFIX = "latex-tutorial-v"

VERSION  = $(shell head VERSION)
# OR try to guess directly from the last git tag
#VERSION    = $(shell  git describe --tags $(LAST_TAG_COMMIT) | sed "s/^$(TAG_PREFIX)//")
MAJOR      = $(shell echo $(VERSION) | sed "s/^\([0-9]*\).*/\1/")
MINOR      = $(shell echo $(VERSION) | sed "s/[0-9]*\.\([0-9]*\).*/\1/")
PATCH      = $(shell echo $(VERSION) | sed "s/[0-9]*\.[0-9]*\.\([0-9]*\).*/\1/")
# total number of commits       
BUILD      = $(shell git log --oneline | wc -l | sed -e "s/[ \t]*//g")

#REVISION   = $(shell git rev-list $(LAST_TAG).. --count)
#ROOTDIR    = $(shell git rev-parse --show-toplevel)
NEXT_MAJOR_VERSION = $(shell expr $(MAJOR) + 1).0.0-b$(BUILD)
NEXT_MINOR_VERSION = $(MAJOR).$(shell expr $(MINOR) + 1).0-b$(BUILD)
NEXT_PATCH_VERSION = $(MAJOR).$(MINOR).$(shell expr $(PATCH) + 1)-b$(BUILD)


====================================================================
