#!/bin/bash
lcov --directory . --capture --output-file lcov.info
lcov --remove lcov.info "/usr*" -o lcov.info
lcov --remove lcov.info "*test/*" -o lcov.info
#genhtml --output-directory coverage lcov.info
