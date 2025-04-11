# Makefile to make it easier to call the scripts

.PHONY: compile

compile:
	sh scripts/compile.sh

upload:
	sh scripts/compile_and_upload.sh
