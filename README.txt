Name: Julio Lemus
Perm: 5650569
Email(Google Group email): julio165guy@gmail.com
Umail: juliolemus@umail.ucsb.edu

Explination:
Scanner: Takes care of all token detection and correct enum token typ returning. Feads these values into eatToken function to consume the input stream for the token.
 
Parser includes all the functions for the productions in the my final grammar. Mainly used nextToken and eatToken functions from Scanner to implement Parser. Used the evaluation boolen to distiguish between evalution and nonevluation tests.
Functions recurse down to the Terminals to use them in evalution and in nonevaluation during parsing step.

All cases in the Non-Terminals/functions include the FIrst and Follow cases for each Non-Terminal. If the input does not match any first or follow cases, in returns a parse error by default.
