#!/bin/bash

PROJECT_ROOT=`git rev-parse --show-toplevel`

if ! pushd "${PROJECT_ROOT}/submodule" 1>/dev/null
then
   return 0
fi

cat /dev/null >"${PROJECT_ROOT}/.git/config"
cat /dev/null >"${PROJECT_ROOT}/.gitmodules"

ls -1 | while read dir
do
    pushd "${dir}" 1>/dev/null
    url=`git remote get-url origin`
    path="submodule/${dir}"
    echo '[submodule "'"${path}"'"]' >>"${PROJECT_ROOT}/.git/config"
    echo "   " url = "${url}" >>"${PROJECT_ROOT}/.git/config"
    echo '[submodule "'"${path}"'"]' >>"${PROJECT_ROOT}/.gitmodules"
    echo "   " url = "${url}" >>"${PROJECT_ROOT}/.gitmodules"
    echo "   " path = "${path}" >>"${PROJECT_ROOT}/.gitmodules"
    echo '[submodule "'"${path}"'"]'
    echo "   " url = "${url}"
    echo "   " path = "${path}"
    popd 1>/dev/null
done

popd 1>/dev/null
