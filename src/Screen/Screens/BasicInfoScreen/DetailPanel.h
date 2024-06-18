#pragma once
#include "../../Draw/Drawing.h"
#include "Utility/UnitConverter.h"
#include "Screen/font/Roboto32.h"
#include "Screen/font/Roboto16.h"
#include "Screen/font/firamono8.h"
#include "API/DeviceDetail.h"


class DetailPanel : public Panel
{
    private:
        TextPanel* PV1E, *PV1I,*PV1P;
        TextPanel* PV2E,*PV2I,*PV2P;
        TextPanel* RE, *RI;
        TextPanel* RF, *SF, *TF; //frequencies, sf and tf will be empty (--)
        TextPanel* SE, *SI;
        TextPanel* TE, *TI;
    public:
        DetailPanel(const int& posX, const int& posY, const int& width, const int& height);
        void setValues(const DeviceDetail& details);
};

void DetailPanel::setValues(const DeviceDetail& details)
{
    PV1E->setText(UnitConverter::convertToVoltageUnits(details.PV1.voltage));
    PV1I->setText(UnitConverter::convertToCurrentUnits(details.PV1.current));
    PV1P->setText(UnitConverter::convertToPowerUnits(details.PV1.power));

    PV2E->setText(UnitConverter::convertToVoltageUnits(details.PV2.voltage));
    PV2I->setText(UnitConverter::convertToCurrentUnits(details.PV2.current));
    PV2P->setText(UnitConverter::convertToPowerUnits(details.PV2.power));

    RE->setText(UnitConverter::convertToVoltageUnits(details.R.voltage));
    RI->setText(UnitConverter::convertToCurrentUnits(details.R.current));

    SE->setText(UnitConverter::convertToVoltageUnits(details.S.voltage));
    SI->setText(UnitConverter::convertToCurrentUnits(details.S.current));

    TE->setText(UnitConverter::convertToVoltageUnits(details.T.voltage));
    TI->setText(UnitConverter::convertToCurrentUnits(details.T.current));

    RF->setText(UnitConverter::convertToFrequencyUnits(details.RFrequency));
    SF->setText("---"); //those do not have frequencies, we leave them empty
    TF->setText("---");
}

DetailPanel::DetailPanel(const int& posX, const int& posY, const int& width, const int& height)
                                : Panel(posX,posY,width,height)
{
    const int cellWidth = _width/5;
    const int cellHeight = _height/4;
    const GFXfont* textFont = &Roboto16;
    const GFXfont* dataFont = &FiraMono8;

    int pX=0;
    int pY=0;

    //TOP
    Panel* topPanel = new Panel(pX,pY,width, cellHeight);

    Panel* pv1TxtP = new Panel(pX,0,cellWidth,cellHeight);
    TextPanel* pv1Txt = &(new TextPanel(0,0,"PV1"))->setMiddle().setFont(textFont);
    pv1TxtP->addComponent(pv1Txt);
    pX+=cellWidth;

    Panel* pv2TxtP = new Panel(pX,0,cellWidth,cellHeight);
    TextPanel* pv2Txt = &(new TextPanel(0,0,"PV2"))->setMiddle().setFont(textFont);
    pv2TxtP->addComponent(pv2Txt);
    pX+=cellWidth;

    Panel* RTxtP = new Panel(pX,0,cellWidth,cellHeight);
    TextPanel* RTxt = &(new TextPanel(0,0,"L1"))->setMiddle().setFont(textFont);
    RTxtP->addComponent(RTxt);
    pX+=cellWidth;

    Panel* STxtP = new Panel(pX,0,cellWidth,cellHeight);
    TextPanel* STxt = &(new TextPanel(0,0,"L2"))->setMiddle().setFont(textFont);
    STxtP->addComponent(STxt);
    pX+=cellWidth;

    Panel* TTxtP = new Panel(pX,0,cellWidth,cellHeight);
    TextPanel* TTxt = &(new TextPanel(0,0,"L3"))->setMiddle().setFont(textFont);
    TTxtP->addComponent(TTxt);

    topPanel->addComponent(pv1TxtP).addComponent(pv2TxtP)
              .addComponent(RTxtP).addComponent(STxtP).addComponent(TTxtP);

    //E
    pX=0;
    pY+=cellHeight;

    Panel* EPanel = new Panel(pX,pY,width, cellHeight);

    Panel* PV1EP = new Panel(pX,0,cellWidth,cellHeight);
    PV1E = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    PV1EP->addComponent(PV1E);

    pX+=cellWidth;

    Panel* PV2EP = new Panel(pX,0,cellWidth,cellHeight);
    PV2E = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    PV2EP->addComponent(PV2E);

    pX+=cellWidth;

    Panel* REP = new Panel(pX,0,cellWidth,cellHeight);
    RE = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    REP->addComponent(RE);

    pX+=cellWidth;

    Panel* SEP = new Panel(pX,0,cellWidth,cellHeight);
    SE = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    SEP->addComponent(SE);

    pX+=cellWidth;

    Panel* TEP = new Panel(pX,0,cellWidth,cellHeight);
    TE = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    TEP->addComponent(TE);

    EPanel->addComponent(PV1EP).addComponent(PV2EP)
              .addComponent(REP).addComponent(SEP).addComponent(TEP);

    //I
    pX=0;
    pY+=cellHeight;

    Panel* IPanel = new Panel(pX,pY,_width, cellHeight);

    Panel* PV1IP = new Panel(pX,0,cellWidth,cellHeight);
    PV1I = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    PV1IP->addComponent(PV1I);

    pX+=cellWidth;

    Panel* PV2IP = new Panel(pX,0,cellWidth,cellHeight);
    PV2I = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    PV2IP->addComponent(PV2I);

    pX+=cellWidth;

    Panel* RIP = new Panel(pX,0,cellWidth,cellHeight);
    RI = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    RIP->addComponent(RI);

    pX+=cellWidth;

    Panel* SIP = new Panel(pX,0,cellWidth,cellHeight);
    SI = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    SIP->addComponent(SI);

    pX+=cellWidth;

    Panel* TIP = new Panel(pX,0,cellWidth,cellHeight);
    TI = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    TIP->addComponent(TI);

    IPanel->addComponent(PV1IP).addComponent(PV2IP)
              .addComponent(RIP).addComponent(SIP).addComponent(TIP);

    //P
    pX=0;
    pY+=cellHeight;

    Panel* PPanel = new Panel(pX,pY,_width,cellHeight);

    Panel* PV1PP = new Panel(pX,0,cellWidth,cellHeight);
    PV1P = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    PV1PP->addComponent(PV1P);

    pX+=cellWidth;

    Panel* PV2PP = new Panel(pX,0,cellWidth,cellHeight);
    PV2P = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    PV2PP->addComponent(PV2P);

    pX+=cellWidth;

    Panel* RFP = new Panel(pX,0,cellWidth,cellHeight);
    RF = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    RFP->addComponent(RF);

    pX+=cellWidth;

    Panel* SFP = new Panel(pX,0,cellWidth,cellHeight);
    SF = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    SFP->addComponent(SF);

    pX+=cellWidth;

    Panel* TFP = new Panel(pX,0,cellWidth,cellHeight);
    TF = &(new TextPanel(0,0,""))->setMiddle().setFont(dataFont);
    TFP->addComponent(TF);


    PPanel->addComponent(PV1PP).addComponent(PV2PP)
            .addComponent(RFP).addComponent(SFP).addComponent(TFP);

    addComponent(topPanel).
    addComponent(EPanel).
    addComponent(IPanel).
    addComponent(PPanel);
}

/*
+----+-----+-----+---+---+---+
| -  | PV1 | PV2 | R | S | T |
+----+-----+-----+---+---+---+
| E  |     |     |   |   |   |
| I  |     |     |   |   |   |
| P  |     |     |   | - | - |
+----+-----+-----+---+---+---+

Edit:
  -First column has been deleted
*/