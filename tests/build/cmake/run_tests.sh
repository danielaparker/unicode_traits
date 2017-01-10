#!/bin/bash
set -e

DIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)

cd ${DIR}/../..
${DIR}/unicode_traits_tests
