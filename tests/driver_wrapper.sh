#!/usr/bin/sh

cmd="$@"

test_name=""

while [ "$#" -ne 0 ] ; do
  case $1 in
    --test-name )
      shift
      test_name="$1"
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

