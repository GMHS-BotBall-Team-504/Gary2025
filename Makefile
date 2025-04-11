# Makefile to make it easier to call the scripts

.PHONY: compile

compile:
    cd scripts
    sh compile.sh
    cd ..

upload:
    cd scripts
    sh compile_and_upload.sh
    cd ..
