#pragma once
#include "IExporter.h"
#include "IExportFactory.h"



class TXTExportFactory : public IExportFactory {
public:
	TXTExportFactory();
	~TXTExportFactory();

	IExporter* CreateExporter() override;
};

class TXTExporter : public IExporter {
public:
	TXTExporter();
	~TXTExporter();

	void Export(Content& content, const std::string& path) override;
};


class MDExportFactory : public IExportFactory {
public:
	MDExportFactory();
	~MDExportFactory();

	IExporter* CreateExporter() override;
};

class MDExporter : public IExporter {
public:
	MDExporter();
	~MDExporter();

	void Export(Content& content, const std::string& path) override;
};


class JSONExportFactory : public IExportFactory {
public:
	JSONExportFactory();
	~JSONExportFactory();

	IExporter* CreateExporter() override;
};

class JSONExporter : public IExporter {
public:
	JSONExporter();
	~JSONExporter();

	void Export(Content& content, const std::string& path) override;
};


class XMLExportFactory : public IExportFactory {
public:
	XMLExportFactory();
	~XMLExportFactory();

	IExporter* CreateExporter() override;
};

class XMLExporter : public IExporter {
public:
	XMLExporter();
	~XMLExporter();

	void Export(Content& content, const std::string& path) override;
};