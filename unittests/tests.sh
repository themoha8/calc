#!/bin/bash

EXP1="25 + 8 * 4"
EXP2="(36  + 	10 ) *  2"
EXP3="		11   + 9*6 ^2"
EXP4="(15 + 18) * (18* ( 	23 + 31.5)) %38"
EXP5="(-15- -18 	) * ((-34) +-5 *-2)"

RESULT1=$(echo "$EXP1" | ../calculator)
RESULT2=$(echo "$EXP2" | ../calculator)
RESULT3=$(echo "$EXP3" | ../calculator)
RESULT4=$(echo "$EXP4" | ../calculator)
RESULT5=$(echo "$EXP5" | ../calculator)


RESULT1_1="Answer: 57"
RESULT2_2="Answer: 92"
RESULT3_3="Answer: 335"
RESULT4_4="Answer: 35"
RESULT5_5="Answer: -72"

if [[ "$RESULT1" == *"$RESULT1_1"* ]]; then
	echo "Test is passed for expression \"$EXP1\""
else
	echo "Test is NOT passed for expression \"$EXP1\""
#	echo "Result: $RESULT1"
fi

if [[ "$RESULT2" == *"$RESULT2_2"* ]]; then
	echo "Test is passed for expression \"$EXP2\""
else
	echo "Test is NOT passed for expression \"$EXP2\""
#	echo "Result: $RESULT2"
fi

if [[ "$RESULT3" == *"$RESULT3_3"* ]]; then
	echo "Test is passed for expression \"$EXP3\""
else
	echo "Test is NOT passed for expression \"$EXP3\""
#	echo "Result: $RESULT3"
fi

if [[ "$RESULT4" == *"$RESULT4_4"* ]]; then
	echo "Test is passed for expression \"$EXP4\""
else
	echo "Test is NOT passed for expression \"$EXP4\""
#	echo "Result: $RESULT4"
fi


if [[ "$RESULT5" == *"$RESULT5_5"* ]]; then
	echo "Test is passed for expression \"$EXP5\""
else
	echo "Test is NOT passed for expression \"$EXP5\""
#	echo "Result: $RESULT5"
fi
