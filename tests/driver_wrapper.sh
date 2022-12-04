#!/usr/bin/sh

cmd="$@"

test_name=""

while [ "$#" -ne 0 ] ; do
  case $1 in
    --test-name )
      shift
      test_name="$1"
      ;;
    --log-file )
      shift
      ;;
    --trs-file )
      shift
      ;;
    --color-tests )
      shift
      ;;
    --enable-hard-errors )
      shift
      ;;
    --expect-failure )
      shift
      ;;
    -- )
      break
      ;;
    * )
      ;;
  esac

  shift

done

$cmd

if [ "$?" -eq 0 ] ; then
  echo "ok - $test_name"
else
  echo "not ok - $test_name" 
fi


