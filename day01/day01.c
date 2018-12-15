//
// Advent of Code 2018 - Day 01
// Problem: https://adventofcode.com/2018/day/1
//
// To run on Mac or Linux: `cc day01.c && cat input.txt | ./a.out`
// To run on Windows: (not sure, maybe somebody can help me out on that)
//

#include <stdio.h>
#include <stdlib.h>


typedef struct bucket {
    int value;
    int occupied;
    struct bucket* next;
} bucket;

void insert(int value, bucket* set);
int contains(int value, bucket* set);


#define SEQ_LEN 1000
#define BUCKET_COUNT 60000


bucket set[BUCKET_COUNT];


int main(int argc, char **argv) {
    char c;
    int parsed, buffer_i, sequence_i, current_total, single_total;
    char buffer[20];
    int sequence[SEQ_LEN];

    buffer_i = sequence_i = current_total = single_total = 0;

    // parse complete input into memory
    while((c = getc(stdin)) != EOF) {
        if (c == '\n') {
            buffer[buffer_i] = 0;
            parsed = atoi(buffer);
            sequence[sequence_i++] = parsed;
            buffer_i = 0;
            continue;
        }
        buffer[buffer_i++] = c;
    }

    // loop over the sequence of numbers, breaking once we see a repeat sum
    while(1) {
        if (sequence_i == SEQ_LEN) {
            sequence_i = 0;
            if (single_total == 0)
                single_total = current_total; // total for a single time through sequence (part 1)
        }

        current_total += sequence[sequence_i++];

        if (contains(current_total, set))
            break;
        else
            insert(current_total, set);
    }

    printf("Sum of sequence: %d\n", single_total);
    printf("First duped total: %d\n", current_total);
}


void insert(int value, bucket* set) {
    int slot = abs(value) % (BUCKET_COUNT - 1);
    bucket* candidate = &set[slot];

    while(1) {
        if (!candidate->occupied) {
            candidate->occupied = 1;
            candidate->value = value;
            candidate->next = NULL;
            break;
        } else {
            if (candidate->next == NULL) {
                bucket* fresh = (bucket*)malloc(sizeof(bucket));
                fresh->occupied = 1;
                fresh->value = value;
                fresh->next = NULL;

                candidate->next = fresh;
                break;
            } else {
                candidate = candidate->next;
            }
        }
    }
}


int contains(int value, bucket* set) {
    int slot = abs(value) % (BUCKET_COUNT - 1);
    bucket* candidate = &set[slot];

    while(1) {
        if ((candidate->occupied) && (candidate->value == value)) {
            return 1;
        } else {
            candidate = candidate->next;
            if (candidate == NULL)
                break;
        }
    }

    return 0;
}
