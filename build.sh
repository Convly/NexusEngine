#!/bin/sh

RED='\033[0;31m'
GREEN='\033[1;32m'
NC='\033[0m'

cd Engine/frameworks/
for d in */ ; do
    echo "${GREEN}Building framework $d...${NC}"
    mkdir -p "$d/build" && cd "$d/build" && cmake .. && make -j8 && echo "${GREEN}Done${NC}" || echo "${RED}ERROR WHILE BUILDING $d${NC}" ; cd ../../
done
cd ../../ &&
echo "${GREEN}Cleaning frameworks...${NC}"
rm -rf build/frameworks &&
echo "${GREEN}Done${NC}"
echo "${GREEN}Building engine...${NC}" 
cd build && cmake .. && make -j8
echo "${GREEN}Terminate${NC}"