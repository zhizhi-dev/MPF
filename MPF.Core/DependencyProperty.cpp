#include "stdafx.h"
#include "../include/DependencyProperty.h"
#include "../include/ui/Border.h"

using namespace MPF;
using namespace MPF::Visual;
using namespace MPF::UI;

DependencyProperty<const MPF::Visual::Brush*> Border::BorderBrushProperty(L"BorderBrush");
DependencyProperty<MPF::Visual::Thickness> Border::BorderThicknessProperty(L"BorderThickness");