#pragma once



class Line {
public:
	Line(char* data) {
		for (int i = 0; i < 140; i++) {
			if (data[i]) {
				m_data[i] = data[i];
			}
			else {
				break;
			}
		}
	}

	void SetLineNumber(int line_number) {
		m_line_number = line_number;
	}

private:
	int m_line_number;

	char m_data[140]{};
};

class Content {
public:
	Content() {

	}
	~Content() {

	}

	bool Edit(bool is_editable) {///return true if user change content
		return true;
	}

	void AddLine(Line line) {
		line.SetLineNumber(m_lines.size());
		m_lines.push_back(line);
	}

private:
	std::vector<Line> m_lines;
};