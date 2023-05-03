#!/bin/bash

function SearchForSourceFiles(){
    find -name '*.cpp' -o -name '*.h' -not -path './cppcon14/*' -not -path './benchmark/*' > ${tmp_source_files}
}

function is-app-installed(){
    hash $1 2>&-
    return $?
}

function doDocs(){
    project_root="${1:-./}"
    (
        cd ${project_root}

        is-app-installed doxygen || {
            echo "You don't have doxygen installed (sudo apt-get install doxygen)"
            exit 1
        }

        source_path=./

        temp_dir_path=./.docs/.temp/

        rm -fr ${temp_dir_path}
        mkdir -p ${temp_dir_path}

        temp_conf_path=${temp_dir_path}/doxyconf.tmp
        conf_path=${temp_dir_path}/doxyconf
        files=./.docs/files/doxygen
        tmp_source_files=${temp_dir_path}/tmp_source_files

        doxygen -g ${conf_path}

        [[ ! -f "${tmp_source_files}" ]] && {
            SearchForSourceFiles
        }

        includes=`sed 's;$; ;' ${tmp_source_files} | tr -d '\n'`

        out_directory="./.docs/.temp/"

        sed -e 's/^PROJECT_NAME *=.*/PROJECT_NAME = "'${project_root}'"/g'  \
            -e 's/^GENERATE_LATEX *=.*/GENERATE_LATEX = NO/g' \
            -e 's/^GENERATE_TREEVIEW *=.*/GENERATE_TREEVIEW = NO/g' \
            -e 's/^EXTRACT_ALL *=.*/EXTRACT_ALL = YES/g' \
            -e 's/^EXTRACT_PRIVATE *=.*/EXTRACT_PRIVATE = YES/g' \
            -e 's/^EXTRACT_STATIC *=.*/EXTRACT_STATIC = YES/g' \
            -e 's/^EXTRACT_PRIV_VIRTUAL *=.*/EXTRACT_PRIV_VIRTUAL = YES/g' \
            -e 's/^EXTRACT_LOCAL_METHODS *=.*/EXTRACT_LOCAL_METHODS = YES/g' \
            -e 's;^EXAMPLE_PATH *=.*;EXAMPLE_PATH = '${source_path}';g' \
            -e 's;^EXCLUDE *=.*;EXCLUDE = "docexcl_examples/";g' \
            -e "s;^EXCLUDE_SYMBOLS *=.*;EXCLUDE_SYMBOLS = \.\*Lock \.\*Timer \.\*Node \.\*Logger;g" \
            -e 's/^HIDE_IN_BODY_DOCS *=.*/HIDE_IN_BODY_DOCS = YES/g' \
            -e 's/^SOURCE_BROWSER *=.*/SOURCE_BROWSER = YES/g' \
            -e 's/^HTML_DYNAMIC_SECTIONS *=.*/HTML_DYNAMIC_SECTIONS = NO/g' \
            -e 's/^TAB_SIZE *=.*/TAB_SIZE = 2/g' \
            -e 's/^HAVE_DOT *=.*/HAVE_DOT = YES/g' \
            -e 's/^DOT_GRAPH_MAX_NODES *=.*/DOT_GRAPH_MAX_NODES = 1000/g' \
            -e 's/^MAX_DOT_GRAPH_DEPTH *=.*/MAX_DOT_GRAPH_DEPTH = 100/g' \
            -e 's/^DOT_FONTNAME *=.*/DOT_FONTNAME = Tahoma/g' \
            -e 's/^DOT_FONTSIZE *=.*/DOT_FONTSIZE = 8/g' \
            -e 's/^DOT_MULTI_TARGETS *=.*/DOT_MULTI_TARGETS = YES/g' \
            -e 's/^DOT_TRANSPARENT *=.*/DOT_TRANSPARENT = YES/g' \
            -e 's/^DOT_IMAGE_FORMAT *=.*/DOT_IMAGE_FORMAT = svg/g' \
            -e 's/^INTERACTIVE_SVG *=.*/INTERACTIVE_SVG = YES/g' \
            -e 's/^UML_LOOK *=.*/UML_LOOK = YES/g' \
            -e 's/^UML_LIMIT_NUM_FIELDS *=.*/UML_LIMIT_NUM_FIELDS = 10/g' \
            -e 's/^DOT_UML_DETAILS *=.*/DOT_UML_DETAILS = YES/g' \
            -e 's/^DOT_WRAP_THRESHOLD *=.*/DOT_WRAP_THRESHOLD = 50/g' \
            -e 's/^TEMPLATE_RELATIONS *=.*/TEMPLATE_RELATIONS = YES/g' \
            -e 's/^DIR_GRAPH_MAX_DEPTH *=.*/DIR_GRAPH_MAX_DEPTH = 10/g' \
            -e "s;^IMAGE_PATH *=.*;IMAGE_PATH = ${files};g" \
            -e "s;^INPUT *=.*;INPUT = ${includes};g" \
            -e 's/^CALL_GRAPH *=.*/CALL_GRAPH = YES/g' \
            -e 's/^CALLER_GRAPH *=.*/CALLER_GRAPH = YES/g' \
            -e "s;^OUTPUT_DIRECTORY *=.*;OUTPUT_DIRECTORY = ${out_directory};g" \
            -e "s;^PROJECT_NUMBER *=.*;PROJECT_NUMBER = 1;g" ${conf_path} > ${temp_conf_path} && mv -vf ${temp_conf_path} ${conf_path}

        doxygen ${conf_path}
        echo "Documentation generated to directory '${out_directory}'"
    )
}

set -e

grep -F 'subdir' meson.build | sed "s/.*'\(.*\)'.*/\1/" | while read -r line ; do
    doDocs ${line}
done
