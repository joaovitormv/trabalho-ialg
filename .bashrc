alias ls='ls --color=auto'
alias grep='grep --color'
alias egrep='egrep --color'
alias df='df -Th'
alias l='ls -l'
alias ll='ls -la'
alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'
# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi
host=`ip a | grep 192.168 | cut -c 22,23 | sed 's/[/]//'`
lab=`ip a | grep 192.168 | cut -c 20,20`
export EDITOR=vim
export PS1='\[\033[01;31m\][\[\033[01;37m\]\t\[\033[01;31m\]]\[\033[01;32m\] \u\[\033[01;31m\]@\[\033[01;32m\]DCC0$lab-$host\[\033[01;31m\][\[\033[01;33m\]\w\[\033[01;31m\]]\[\033[01;37m\]$ \[\033[00m\]'

