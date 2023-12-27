#!/bin/bash
## cheat sheet wrapper from cht.sh


CHT_URL="https://cht.sh"
LANG='bash'
CHT_URL="https://cht.sh/${LANG}"

echo -n "Enter you query:"
read QUERY

CHT_URL="https://cht.sh/${LANG}/${QUERY}"

if tmux list-sessions>/dev/null; then

	tmux split-window -hf -v bash -c "curl -s "${CHT_URL}"|less"

else

	curl -s "${CHT_URL}"|less

fi
