# howto

I keep this repo as simple as possible so anyone can pick it up.

## What is my workflow?

1. I find ASCII art online, using keywords such as "ANSI art", "ASCII art", "text art",
   while avoiding unrenderable Braille/Japanese.

   (See "Charsets" below for more information.)
2. I deposit the art into `art/$ART_NAME`.
3. Using `neovim` for
   * Raw edits
   * Macros
   * Visual block mode,

   I personalize the art by
   * Adding color via ANSI escape codes
   * Adding shapes using ASCII or copy-pasted CP437 characters
   * Combining shapes, e.g. making text using an ASCII art generator.
     * I do not recommend _image_-to-ASCII generators. They are
       low-quality compared to actual text artists.

   For example, I'd run `neovim howto/0* art/$ART_NAME` and get paintin'.

4. While using `neovim`, I run `./test art/$ART_NAME` in a second
   terminal to iterate live and preview immediately upon filesave.
   * Be careful of colors. TTY colors are always a bit different.
   * Be careful of symbols.
      * Your desktop's terminal will have a metrically-different font compared to the TTY.
      * ¾ (and other symbols) renders on most desktop terminals but not on the TTY.
5. Once finished, I credit the artist and describe what I did in `art/.$ART_NAME`.

## Charsets — which can I use?

| "Charset" | What does it do? | How did I figure it out? |
| ------- | ---------------- | ------------------------ |
| [ASCII](https://en.wikipedia.org/wiki/ASCII#Character_set)   | Basic text. Just use your keyboard | Duh |
| [Code Page 437](https://en.wikipedia.org/wiki/Code_page_437#Character_set) | Gives cool symbols, like [box-drawing characters](https://en.wikipedia.org/wiki/Box-drawing_characters). Usually, CP437 characters are converted to UTF-8 before rendering. | I hypothesized that the TTY used extended ASCII. After testing other ISO charsets as well as CP437 (e.g. [this script](https://stackoverflow.com/a/60355364) helped preliminary testing but I noticed it missed CP437 rows 0x and 1x), I found that I was correct, at least for default console fonts. |
| ANSI escape sequences: [cursor motion](https://en.wikipedia.org/wiki/ANSI_escape_code#Control_Sequence_Introducer_commands) and [16-color](https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit) | Recolors the foreground/background of text, or moves the cursor. On an 8-color TTY, ANSI escapes can't be fancy and make blinking or underlines. | I investigated the output of `fastfetch > test_file` and did quite a bit of DuckDuckGoing on escape sequences. |
| agetty special characters | Shows information about the machine by turning escape sequences such as `\r` into `6.12.21-gentoo-dist`. | I looked in [agetty source code](https://github.com/util-linux/util-linux/blob/995a4e2341f699e9eb7f2e2c529e1c8802a61170/term-utils/agetty.c#L2694) after noticing the use of `\S` and other sequences in my machine's uncustomized `/etc/issue` |

Judging by the output of `tput colors`, we only have the 16 colors. Run a fetch utility such as `fastfetch` to see these colors.

## Any other tips?

Run `./test howto/00any-of-the-files-here` for useful references.
