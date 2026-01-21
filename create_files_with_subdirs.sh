#Creating variables that limit the amount of files allowed within a file as well as the name for the log file and programming languages being used

LOG_FILE="script.log"
NUM_SUB_DIR=10
NUM_FILES_PER_DIR=10
START_FILE_NUM=101
START_TUSER_NUM=501
PROG_LANG=("Java" "Python" "C" "C#" "C++" "Java Script" "PHP" "Ruby" "Cobalt" "Go")

#Setting up the log message format

log_message(){
	local message="$1"
	echo "[$(date '+%Y-%m-%d %H:%M:%S')] $message" >> "$LOG_FILE"
}

#start of the script to create the main directory

log_message "Start"

MAIN_DIR="$(date '+%Y-%m-%d %H:%M:%S')"
mkdir "$MAIN_DIR"
log_message "Created main directory: $MAIN_DIR"

cd "$MAIN_DIR"

#Creating the subdirectories and log message for their creation

for i in $(seq 0 $((NUM_SUB_DIR - 1))); do
	sub_dir_num=$((START_FILE_NUM + i))
	SUB_DIR="file$sub_dir_num"
	mkdir "$SUB_DIR"
	log_message "Created subdirectory: $SUB_DIR"

	#Creating the text files and inputing a single programming language into each file and moving the created text files into the subdirectories

	for j in $(seq 0 $((NUM_FILES_PER_DIR - 1))); do
		file_num=$((START_TUSER_NUM + j))
		FILE_NAME="tuser$file_num.txt"
		LANG="${PROG_LANG[$j]}"
		echo "$LANG" > "$FILE_NAME"
		mv "$FILE_NAME" "$SUB_DIR/"
		log_message "Created file: $SUB_DIR/$FILE_NAME with the programming language: $LANG and moved it into the folder."
	done
done

#Specifying that the scirpt is complete

log_message "Finished"

echo "Script completed"
