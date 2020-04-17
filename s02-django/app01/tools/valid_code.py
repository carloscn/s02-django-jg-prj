from PIL import Image,ImageDraw,ImageFont
import random
from io import BytesIO

def get_valid_code_img(reuqest):
    def get_random_color():
        return (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))


    img = Image.new("RGB", (270, 40), color=get_random_color())
    draw = ImageDraw.Draw(img)
    one_font = ImageFont.truetype("static/font/one.ttf", size=20)

    valid_code_str = ""
    for i in range(5):
        random_num = str(random.randint(0, 9))
        random_low_alpha = chr(random.randint(95, 122))
        random_upper_alpha = chr(random.randint(65, 90))
        random_char = random.choice([random_num, random_low_alpha, random_upper_alpha])
        draw.text((i * 50 + 20, 5), random_char, get_random_color(), font=one_font)

        #     保存验证码字符串
        valid_code_str += random_char

    width = 270
    height = 40
    for i in range(5):
        x1 = random.randint(0, width)
        x2 = random.randint(0, width)
        y1 = random.randint(0, height)
        y2 = random.randint(0, height)
        draw.line((x1, y1, x2, y2), fill=get_random_color())

    for i in range(50):
        draw.point([random.randint(0, width), random.randint(0, height)], fill=get_random_color())
        x = random.randint(0, width)
        y = random.randint(0, height)
        draw.arc((x, y, x + 4, y + 4), 0, 90, fill=get_random_color())

    reuqest.session["valid_code_str"] = valid_code_str
    '''
    1 生成一个随机字符串asdasfsa
    2 COOKIE {'sessionid':'asdasfsa'}
    3 django-session
      session-key        session-data
      asdasfsa           {" valid_code_str":"这里就是随机验证码“}
    
    '''

    f = BytesIO()
    img.save(f, 'png')
    data = f.getvalue()
    return data