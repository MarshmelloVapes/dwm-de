if status is-interactive
    # Commands to run in interactive sessions can go here
    alias v nvim
    alias sv "sudo nvim"
    alias ytaudio "yt-dlp -x --audio-format mp3"
    alias hx helix
    alias sd "udisksctl mount -b /dev/mmcblk0p1"
    alias ppd "~/.scripts/PPD.sh"
end

function fish_greeting
end

function fish_prompt -d "Write out the prompt"
    # This shows up as USER@HOST /home/user/ >, with the directory colored
    # $USER and $hostname are set by fish, so you can just use them
    # instead of using `whoami` and `hostname`
    printf '%s%s%s@%s%s %s%s%s $ ' \
        (set_color $fish_color_quote) $USER \
        (set_color normal) \
        (set_color $fish_color_comment) $hostname \
        (set_color $fish_color_cwd) (prompt_pwd) (set_color normal)
end

if status is-login
    udiskctl mount -b /dev/mmcblk0p1
    if not set -q DISPLAY; and string match -r '^/dev/tty[0-9]$' (tty)
        exec startx
    end
end


starship init fish | source
