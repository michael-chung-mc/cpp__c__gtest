#include "canvas.h"
#include "comparinator.h"
#include "color.h"
#include "pch.h"

Canvas::Canvas(int width, int height) {
	this->mbrWidth = width;
	this->mbrHeight = height;
	this->mbrGrid.clear();
	for (int i = 0; i < mbrWidth; ++i)
	{
		std::vector<Color> column;
		mbrGrid.push_back(column);
		for (int j = 0; j < mbrHeight; ++j)
		{
			mbrGrid[i].push_back(Color(0, 0, 0));
		}
	}
};

bool Canvas::isClean() {
	Comparinator ce = Comparinator();
	Color black = Color(0, 0, 0);
	bool clean = true;
	for (int i = 0; i < mbrGrid.size(); ++i)
	{
		for (int j = 0; j < mbrGrid[0].size(); ++j)
		{
			if (!ce.checkTuple(mbrGrid[i][j], black))
			{
				clean = false;
				break;
			}
		}
	}
	return clean;
};

bool Canvas::inBounds(int x,int y) {
	return mbrGrid.size() > 0 && mbrGrid[0].size() > 0 && x >= 0 && x < mbrGrid.size() && y >= 0 && y < mbrGrid[0].size();
}

void Canvas::setPixel(int x, int y, Color c) {
	if (inBounds(x,y)) { mbrGrid[x][y] = c; }
}

void Canvas::fill(Color x) {
	for (int i = 0; i < mbrGrid.size(); ++i)
	{
		for (int j = 0; j < mbrGrid[i].size(); ++j)
		{
			setPixel(i, j, x);
		}
	}
}

Color Canvas::getPixel(int x, int y) {
	if (inBounds(x, y)) { return mbrGrid[x][y]; }
	return Color(0,0,0);
}

std::string Canvas::getPPM()
{
	//std::string ppm = "P3\n" + std::to_string(w) + " " + std::to_string(h) + "\n" + "255\n";
	std::string* ppm = new std::string("P3\n" + std::to_string(mbrWidth) + " " + std::to_string(mbrHeight) + "\n" + "255\n");
	std::string buffer = "";
	int cnr = 0;
	int cng = 0;
	int cnb = 0;
	// width = row & height = column
	for (int j = 0; j < mbrHeight; ++j)
	{
		for (int i = 0; i < mbrWidth; ++i)
		{
			cnr = std::min((int)std::round((255 * mbrGrid[i][j].mbrRed)), 255);
			cnr = cnr > 0 ? cnr : 0;
			std::string clampedNormalizedRed = std::to_string(cnr);
			if (buffer.size() + clampedNormalizedRed.size() > getPPMLineWidth())
			{
				*ppm += buffer;
				*ppm = isspace((*ppm)[(*ppm).size() - 1]) ? (*ppm).substr(0, (*ppm).size() - 1) : *ppm;
				buffer = "\n" + clampedNormalizedRed + " ";
			}
			else
			{
				buffer += clampedNormalizedRed + " ";
			}
			cng = std::min((int)std::round((255 * mbrGrid[i][j].mbrGreen)), 255);
			cng = cng > 0 ? cng : 0;
			std::string clampedNormalizedGreen = std::to_string(cng);
			if (buffer.size() + clampedNormalizedGreen.size() > getPPMLineWidth())
			{
				*ppm += buffer;
				*ppm = isspace((*ppm)[(*ppm).size() - 1]) ? (*ppm).substr(0, (*ppm).size() - 1) : *ppm;
				buffer = "\n" + clampedNormalizedGreen + " ";
			}
			else
			{
				buffer += clampedNormalizedGreen + " ";
			}
			cnb = std::min((int)std::round((255 * mbrGrid[i][j].mbrBlue)), 255);
			cnb = cnb > 0 ? cnb : 0;
			std::string clampedNormalizedBlue = std::to_string(cnb);
			if (buffer.size() + clampedNormalizedBlue.size() > getPPMLineWidth())
			{
				*ppm += buffer;
				*ppm = isspace((*ppm)[(*ppm).size() - 1]) ? (*ppm).substr(0, (*ppm).size() - 1) : *ppm;
				buffer = "\n" + clampedNormalizedBlue + " ";
			}
			else
			{
				buffer += clampedNormalizedBlue + " ";
			}
		}
		*ppm += buffer;
		*ppm = isspace((*ppm)[(*ppm).size() - 1]) ? (*ppm).substr(0, (*ppm).size() - 1) : *ppm;
		buffer = "\n";
		//std::cout << "rendered line:" << std::to_string(j) << std::endl;
	}
	// cutoff extra whitespace
	*ppm = isspace((*ppm)[(*ppm).size() - 1]) ? (*ppm).substr(0, (*ppm).size() - 1) : *ppm;
	*ppm += "\n";
	return *ppm;
}

void Canvas::save() {
	std::ofstream file(getPPMFilename(true));
	std::cout << "to saving ..." << std::endl;
	std::string data = getPPM();
	if (file.is_open()) {
		file << data;
	}
	file.close();
	std::cout << "saved" << std::endl;
}