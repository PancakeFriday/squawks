import sys
import numpy
from PIL import Image, ImageFont, ImageDraw, ImageEnhance

# it's just a script guys, global vars are ok
# the background of the button
bg = Image.open(sys.argv[1]).convert('RGBA')
bgw, bgh = bg.size

basecolor = (149, 184, 209)

def make_part(partnum):
    if partnum == 0:
        color1 = basecolor + (50,)
        color2 = basecolor + (255,)
    if partnum == 1:
        color1 = basecolor + (50,)
        color2 = basecolor + (255,)
    if partnum == 2:
        color1 = basecolor + (50,)
        color2 = basecolor + (255,)

    # blank image for the text
    txt = Image.new('RGBA', bg.size, (255,255,255,0))
    font = ImageFont.truetype("BebasNeue Bold.ttf", int(sys.argv[3]))
    draw = ImageDraw.Draw(txt)

    tw, th = draw.textsize(sys.argv[2], font=font)

    off = ((bgw-tw)/2, (bgh-th)/2)

    # I'm not in the mood to think of a better way
    if partnum == 0:
        draw.text(off, sys.argv[2], font=font, fill=color1)
        draw.text(numpy.subtract(off,1), sys.argv[2], font=font, fill=color1)
        draw.text(numpy.subtract(off,2), sys.argv[2], font=font, fill=color1)
        draw.text(numpy.subtract(off,3), sys.argv[2], font=font, fill=color2)

        enhancer = ImageEnhance.Brightness(txt)
        txtmod = enhancer.enhance(1)

    if partnum == 1:
        draw.text(off, sys.argv[2], font=font, fill=color1)
        draw.text(numpy.subtract(off,1), sys.argv[2], font=font, fill=color1)
        draw.text(numpy.subtract(off,2), sys.argv[2], font=font, fill=color1)
        draw.text(numpy.subtract(off,3), sys.argv[2], font=font, fill=color2)

        enhancer = ImageEnhance.Brightness(txt)
        txtmod = enhancer.enhance(1.3)

    if partnum == 2:
        draw.text(off, sys.argv[2], font=font, fill=color1)
        draw.text(numpy.subtract(off,1), sys.argv[2], font=font, fill=color2)

        enhancer = ImageEnhance.Brightness(txt)
        txtmod = enhancer.enhance(1.3)

    out = Image.alpha_composite(bg, txtmod)

    return out

if len(sys.argv) < 4:
    print("Usage: create_button.py button_background text fontsize")
    sys.exit(0)

out = Image.new('RGBA', (bgw, bgh*3), (255,255,255,0))
out.paste(make_part(0), (0,0))
out.paste(make_part(1), (0,bgh))
out.paste(make_part(2), (0,2*bgh))
# out = make_part(0)

# out.show()
out.save("button.png")
