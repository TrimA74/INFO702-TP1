#include "GrayLevelImage2D.hpp"

GrayLevelImage2D::GrayLevelImage2D( int w, int h, GrayLevel g) : m_data(w*h,g) , m_width(w) , m_height(h) {
}

GrayLevelImage2D::GrayLevelImage2D () : m_data(0) , m_width(0) , m_height(0) {
}

int GrayLevelImage2D::index(int x, int y) const {
	return m_width * y + x;

}
int GrayLevelImage2D::w() const {
	return m_width;
}
int GrayLevelImage2D::h() const {
	return m_height;
}

GrayLevelImage2D::GrayLevel GrayLevelImage2D::at( int i , int j) const {
	return m_data[GrayLevelImage2D::index(i,j)];
}
GrayLevelImage2D::GrayLevel& GrayLevelImage2D::at(int i, int j){
	return m_data.at(GrayLevelImage2D::index(i,j));
}

GrayLevelImage2D::Iterator GrayLevelImage2D::begin() {
	return Iterator(*this,0,0);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::end() {
	return Iterator(*this,w(),h()-1);
}
GrayLevelImage2D::Iterator GrayLevelImage2D::start(int x, int y) {
	return Iterator(*this,x,y);
}

bool GrayLevelImage2D::importPGM( std::istream & input ){
	if ( ! input.good() ) {
		std::cerr << "Probleme !";
		return false;
	}
	std::string str;
	std::string type;
	std::getline(input,str);
	type = str;
	std::getline(input,str);
	std::getline(input,str);

	int w,h;
	std::istringstream istr( str );
	istr >> w >> h;

	m_width = w;
	m_height = h;
	m_data.resize(w*h);
	std::cout << "type " << type << std::endl;
	std::cout << "width " << w << std::endl;
	std::cout << "height " << h << std::endl;

	if(type == "P2"){
		input >> std::skipws;
        for ( Iterator it = begin(), itE = end(); it != itE; ++it ) {
            int g;
            input >> g;
            *it = g;
        }
    }else{
        input >> std::noskipws;
        for ( Iterator it = begin(), itE = end(); it != itE; ++it ) {
            GrayLevel g;
            input >> g;
            *it = g;
        }
    }
    return true;
}

bool GrayLevelImage2D::exportPGM( std::ostream & output, bool ascii_mode){
    
    if(ascii_mode)
    {
        output << "P2\n";
        output << "#Commentaire :)\n";
        output << w() << " " << h() << "\n";
        output << "255\n";
        std::ostream_iterator<int> out_it(output, " ");
        std::copy(this->begin(),this->end(),out_it);
    }else{
        output << "P5\n";
        output << "#Commentaire :)\n";
        output << w() << " " << h() << "\n";
        output << "255\n";

        std::ostream_iterator<GrayLevel> out_it(output);
        std::copy(this->begin(),this->end(),out_it);
    }
    
    return true;
}

bool GrayLevelImage2D::filtrageMedian (int k ) {

}



