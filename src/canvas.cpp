#include "pch.h"

Canvas::Canvas(int width, int height) {
	w = width;
	h = height;
	grid.clear();
	for (int i = 0; i < w; i++)
	{
		std::vector<Color> column;
		grid.push_back(column);
		for (int j = 0; j < h; j++)
		{
			grid[i].push_back(Color(0, 0, 0));
		}
	}
};

bool Canvas::isClean() {
	Comparinator ce = Comparinator();
	Color black = Color(0, 0, 0);
	bool clean = true;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (!ce.equalTuple(grid[i][j], black))
			{
				clean = false;
				break;
			}
		}
	}
	return clean;
}

bool Canvas::inBounds(int x,int y) {
	return grid.size() > 0 && grid[0].size() > 0 && x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

void Canvas::setPixel(int x, int y, Color c) {
	if (inBounds(x,y)) { grid[x][y] = c; }
}

void Canvas::fill(Color x) {
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			setPixel(i, j, x);
		}
	}
}

Color Canvas::getPixel(int x, int y) {
	if (inBounds(x, y)) { return grid[x][y]; }
	return Color(0,0,0);
}

std::string Canvas::getPPM()
{
	std::string ppm = "P3\n" + std::to_string(w) + " " + std::to_string(h) + "\n" + "255\n";
	std::string buffer = "";
	int cnr = 0;
	int cng = 0;
	int cnb = 0;
	// width = row & height = column
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			cnr = std::min((int)std::round((255 * grid[i][j].r)), 255);
			cnr = cnr > 0 ? cnr : 0;
			std::string clampedNormalizedRed = std::to_string(cnr);
			if (buffer.size() + clampedNormalizedRed.size() > getPPMLineWidth())
			{
				ppm += buffer;
				ppm = isspace(ppm[ppm.size() - 1]) ? ppm.substr(0, ppm.size() - 1) : ppm;
				buffer = "\n" + clampedNormalizedRed + " ";
			}
			else
			{
				buffer += clampedNormalizedRed + " ";
			}
			cng = std::min((int)std::round((255 * grid[i][j].g)), 255);
			cng = cng > 0 ? cng : 0;
			std::string clampedNormalizedGreen = std::to_string(cng);
			if (buffer.size() + clampedNormalizedGreen.size() > getPPMLineWidth())
			{
				ppm += buffer;
				ppm = isspace(ppm[ppm.size() - 1]) ? ppm.substr(0, ppm.size() - 1) : ppm;
				buffer = "\n" + clampedNormalizedGreen + " ";
			}
			else
			{
				buffer += clampedNormalizedGreen + " ";
			}
			cnb = std::min((int)std::round((255 * grid[i][j].b)), 255);
			cnb = cnb > 0 ? cnb : 0;
			std::string clampedNormalizedBlue = std::to_string(cnb);
			if (buffer.size() + clampedNormalizedBlue.size() > getPPMLineWidth())
			{
				ppm += buffer;
				ppm = isspace(ppm[ppm.size() - 1]) ? ppm.substr(0, ppm.size() - 1) : ppm;
				buffer = "\n" + clampedNormalizedBlue + " ";
			}
			else
			{
				buffer += clampedNormalizedBlue + " ";
			}
		}
		ppm += buffer;
		ppm = isspace(ppm[ppm.size() - 1]) ? ppm.substr(0, ppm.size() - 1) : ppm;
		buffer = "\n";
	}
	// cutoff extra whitespace
	ppm = isspace(ppm[ppm.size() - 1]) ? ppm.substr(0, ppm.size() - 1) : ppm;
	return ppm += "\n";
}

void Canvas::save() {
	std::ofstream file;
	file.open(getPPMFilename());
	file << getPPM();
	file.close();
}