#!/bin/bash

EXEC="temple"

# Define ANSI color codes
RESET="\e[0m"
RED="\e[31m"
GREEN="\e[32m"
ORANGE="\e[33m"
BLUE="\e[34m"
CYAN="\e[36m"

function init {
	pad=$(printf '%.1s' "."{1..70})
	padlength=71

	make
	if [ $? -ne 0 ]; then
		printf "Makefile failed!\n"
		exit 1
	fi

	mkdir -p output/words
	mkdir -p output/cipher/caesar
	mkdir -p output/cipher/vigenere
	mkdir -p output/cipher/addition
	mkdir -p output/agram/
}

function print_result {
	test_name="$1"
	result="$2"

	if [ "$result" == "passed" ]; then
		color="$GREEN"
	elif [ "$result" == "failed" ]; then
		color="$RED"
	else
		color="$RESET"
	fi
	printf "${ORANGE}%s${BLUE}" "Test $test_name"
	printf "%*.*s" 0 $((padlength - 9 - ${#test_name} - ${#result} )) "$pad"
	printf "${color}%s${RESET}\n" "$result"
}

function check_task {
	start_test_id=0
	end_test_id=4

	printf "${CYAN}%s..........................MAGIC WORDS..............................\n"

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/words/input${test_id}.txt"
            ref_file="./ref/words/ref${test_id}.txt"
            output_file="./output/words/output${test_id}.txt"
	
		./$EXEC < "$test_file" > "$output_file"
	
		if [ -f "$output_file" ]; then
			if diff -w "$output_file" "$ref_file" &> /dev/null; then
				print_result "${test_id}" "passed"
			else 
				print_result "${test_id}" "failed"
			fi
		fi
		rm -f "$output_file"
	done

    echo " "

	printf "${CYAN}%s............................MAGIC CIPHER...........................\n"

	for subtask in "caesar" "vigenere" "addition"; do
		start_test_id=0
		end_test_id=4

		if [ $subtask == "caesar" ]; then
			printf "${CYAN}%s...............................CAESAR..............................\n"
		elif [ $subtask == "vigenere" ]; then
			printf "${CYAN}%s..............................VIGENERE.............................\n"
		elif [ $subtask == "addition" ]; then
			printf "${CYAN}%s..............................ADDITION.............................\n"
		fi

		for test_id in $(seq $start_test_id $end_test_id); do
			test_file="./input/cipher/${subtask}/input${test_id}.txt"
			ref_file="./ref/cipher/${subtask}/ref${test_id}.txt"
			output_file="./output/cipher/${subtask}/output${test_id}.txt"

			./$EXEC < "$test_file" > "$output_file"

			if [ -f "$output_file" ]; then
				if diff -w "$output_file" "$ref_file" &> /dev/null; then
					print_result "${test_id}" "passed"
				else 
					print_result "${test_id}" "failed"
				fi
			fi
		done
	done

	echo " "

	start_test_id=0
	end_test_id=4

	printf "${CYAN}%s.............................TWO GRAMS.............................\n"

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/agram/input${test_id}.txt"
			ref_file="./ref/agram/ref${test_id}.txt"
			output_file="./output/agram/output${test_id}.txt"

		./$EXEC < "$test_file" > "$output_file"

		if [ -f "$output_file" ]; then
			if diff -w "$output_file" "$ref_file" &> /dev/null; then
				print_result "${test_id}" "passed"
			else 
				print_result "${test_id}" "failed"
			fi
		fi
		rm -f "$output_file"
	done

	echo " "
}

init
check_task
make clean &> /dev/null