The program helps solve for the resistors that will minimise error in the voltage feedback circuit.
Involing 4 resistors to make 2 voltage dividers.
The first divider is used on the control IC's reference voltage for comparative reference in the feedback loop (or an external reference voltage like from a 5V linear regulator).
The second divider takes the SMPS output voltage for the comparitor in the feedback loop.

The program depends on a list of available resistor to the user. There is a standard set of {10, 22, 47, 68} multiples. From 10 Ohm up to 1M Ohms.
A new dataset of resistor will be required if the standard set is insufficient.
