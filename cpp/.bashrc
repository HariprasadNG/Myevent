case $- in
	*i*)    #interactive
		export DSRCUSER=nghariprasad
	    	export PATH=${PATH}:/usr/local/bin:${HOME}/bin:/sbin
	        export MANPATH=/usr/local/man:/usr/share/man:/usr/man
		source ~/.dsrc
	;;
esac


echo ".bashrcfile is running..."
#### Custom Aliases
alias vi='vim'
alias startvnc='vncserver :1 -name vnc -depth 16 -geometry 1366x768'
alias grep='grep --color=auto --line-number'
alias egrep='egrep --color=auto --line-number'
alias fgrep='fgrep --color=auto --line-number'
alias ls='ls --color=auto'

alias src='cd /mnt/src/nghariprasad/p4-asg/hari-ive/src'
alias bld='cd /mnt/src/nghariprasad/p4-asg/hari-ive/build'

function finder { 
    find . -name "$1" | xargs grep $2 $3 2>/dev/null; 
}

###


####All git####
function glog {
    git log --oneline --color $1 $2;
}

function gc {
    git checkout $1;
}

alias gb="git branch"
alias gammend="git commit --amend"
alias gstatus="git status"

function grebase {
    git rebase -i $i;
}

function gfethc {
    git fetch $1;
}

function gnbranch {
    git checkout -b $1 ssh_origin/$1;
}

function gupdate {
    git fetch ref;
    git pull ref master;
}

function gitStat {
git log --oneline --all --no-merges --since=\"$1\" --author=$2 --shortstat |grep "files changed" | awk '{files+=$2; inserted+=$5; deleted+=$7} END {print "files changed", files, "lines inserted:", inserted, "lines deleted:", deleted}'
}

function stopds {   
    kill -9 `ps -ef| grep $1 | grep -v grep | awk '{print $2}'`;
}

function gitCommits {
git log --oneline --all --no-merges --since=\"$1\" --author=$2|grep -v "\[am\]"
}
