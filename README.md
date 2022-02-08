# MOPL - Matt's Operational Precision Library

This library handles arithmetics on very big arbitrary precision numbers with a set number of integer and decimal figures

Functions:

* **MNumber** MInit(**uint64_t** _integerFigures_, **uint64_t** _decimalFigures_);
* **MNumber** MAdd(**MNumber** _a_, **MNumber** _b_); 
* **MNumber** MSubtract(**MNumber** _a_, **MNumber** _b_);
* **MNumber** MExponent(**MNumber** _a_, **MNumber** _b_); 
* **MNumber** MMultiplicate(**MNumber** _a_, **MNumber** _b_);
* **MNumber** MDivide(**MNumber** _a_, **MNumber** _b_); 
* **MNumber** MModulo(**MNumber** _a_, **MNumber** _b_);
* **MNumber** MIntegerDivision(**MNumber** _a_, **MNumber** _b_);
* **MNumber** MAbsolute(**MNumber** _a_);
* **int** MCompare(**MNumber** _a_, **MNumber** _b_);
