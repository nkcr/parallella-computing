The first steps to understand parallella and epiphany.

* game-of-life - each eCore acts as an independant cell, no synchronizations performed
* hello-from-epiphany - each eCore writes to sdram and the result is read by the ARM
* hello-from-neighbor-ecore - each eCore writes to the sdram it's neighbor's id (got with `e_read`, the result is then read by the ARM
* hello-from-neighbor-ecore2 - same but uses direct address to communicate

Note that code written may not be cleaned. Consider it as a learning draft.
