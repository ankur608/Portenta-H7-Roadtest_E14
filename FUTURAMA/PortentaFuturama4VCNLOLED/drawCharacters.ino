void drawLila()
{
    oled.drawBitmap(Lila);//Display Logo
    oled.display();
}

void drawBender()
{
    oled.drawBitmap(Bender);//Display Logo
    oled.display();
}

void drawAmy()
{
    oled.drawBitmap(Amy);//Display Logo
    oled.display();
}

void drawZoid()
{
    oled.drawBitmap(Zoid);//Display Logo
    oled.display();
}

void drawProf()
{
    oled.drawBitmap(Prof);//Display Logo
    oled.display();
}

void drawPhil()
{
    oled.drawBitmap(Phil);//Display Logo
    oled.display();
}

void drawBanner()
{
 int middleZ = (oled.getLCDWidth() / 2)-14;
 int middleX = oled.getLCDWidth() / 2;
 int middleY = oled.getLCDHeight() / 2;
 oled.clear(PAGE);
 oled.setCursor(middleZ - (oled.getFontWidth() * (2)),
                middleY - (oled.getFontHeight() / 2)-16);
 oled.print("FUTURAMA"); 
 oled.setCursor(middleX - (oled.getFontWidth() * (2)+20),
                middleY - (oled.getFontHeight() / 2)+6);
 oled.print("Ranked  by----------");
 oled.setCursor(middleX - (oled.getFontWidth() * (2)+10),
                middleY - (oled.getFontHeight() / 2)+20);
 oled.print("(INTEL)");
 oled.display();
}
