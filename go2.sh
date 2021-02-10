#./asm_o ./testop/01_live-comment_end_of_line.s
#02_ld-dir_value_is_empty_reg_is_valid
#16_aff-reg_is_valid
#02_ld-ind_value_is_big_reg_is_valid
#15_lfork-no_arg
#14_lldi-three_registers_first_value_too_big
#02_ld-ind_value_is_neg_reg_is_valid
#10_ldi-all_registers_are_valid_comment_end_of_line
#12_fork-dir_value_is_big
N="12_fork-dir_value_is_big"
D="./testop/"
S=".s";
C=".cor";
F="1500";
S1=$N$S;
C2=$N$C;
./asm_o $D$S1
echo "$C2"
./o_corewar -d 1 $D$C2 > f0
./o_corewar -d $F $D$C2 > f1
./corewar -d $F $D$C2 > f2


#./o_corewar  ./Compiled/helltrain.cor > f1
#./corewar  ./Compiled/helltrain.cor > f2

#---./o_corewar -d 1740 ./Compiled/turtle.cor  > f1
#---./corewar -d 1740 ./Compiled/turtle.cor  > f2
#ok ./o_corewar -d 4000 ./Compiled/bigzork.cor > f1
#ok ./corewar -d 4000 ./Compiled/bigzork.cor  > f2
#./o_corewar ./Compiled/bee_gees.cor ./Compiled/helltrain.cor > f1
#./corewar ./Compiled/bee_gees.cor ./Compiled/helltrain.cor > f2

if [[ $(diff -u f1 f2) == "" ]]; then
  echo "OK"
fi
#diff -u f1 f2

#Сегфолты
#.02_ld-ind_value_is_big_reg_is_valid /go.sh: line 16: 81820 Segmentation fault: 11  ./corewar -d $F $D$C2 > f2
#16_aff-reg_is_valid
