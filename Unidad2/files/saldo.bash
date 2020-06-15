# generar archivo ($1) con saldo (integer $2)

printf "0: %.8x" $2 | sed -e 's/0\: \(..\)\(..\)\(..\)\(..\)/0\: \4\3\2\1/' | xxd -r -p > $1
