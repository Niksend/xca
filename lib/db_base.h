/*
 * Copyright (C) 2001 Christian Hohnstaedt.
 *
 *  All rights reserved.
 *
 *
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  - Neither the name of the author nor the names of its contributors may be 
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * This program links to software with different licenses from:
 *
 *	http://www.openssl.org which includes cryptographic software
 * 	written by Eric Young (eay@cryptsoft.com)"
 *
 *	http://www.sleepycat.com
 *
 *	http://www.trolltech.com
 * 
 *
 *
 * http://www.hohnstaedt.de/xca
 * email: christian@hohnstaedt.de
 *
 * $Id$
 *
 */                           


#include "../config.h"
#ifdef HAVE_DB3_DB_CXX_H
#include <db3/db_cxx.h>
#elif HAVE_DB_DB_CXX_H
#include <db/db_cxx.h>
#else
#include <db_cxx.h>
#endif
#ifdef HAVE_QACCESSIBLE_H
#define qt3 1
#endif
#include <qlistview.h>
#include <qlist.h>
#include <qpixmap.h>
#include "pki_base.h"

#ifndef DB_BASE_H
#define DB_BASE_H


class db_base: public QObject
{
		
    protected:
	Db *data;
	DbEnv *dbenv;
	QListView *listView;
	QList<pki_base> container;
	bool _writePKI(pki_base *pki, bool overwrite, DbTxn *tid = NULL);
	bool _removePKI(pki_base *pki, DbTxn *tid = NULL);
    public:
	db_base(DbEnv *dbe, string DBfile, string db);
	virtual ~db_base();
	virtual pki_base *newPKI(){
		CERR<<"VIRTUAL CALLED: newPKI\n"; return NULL;}
	virtual bool updateView();
	virtual void updateViewPKI(pki_base *pki);
	virtual bool insertPKI(pki_base *pki);
	virtual bool deletePKI(pki_base *pki);
	virtual bool updatePKI(pki_base *pki);
	virtual bool renamePKI(pki_base *pki, string desc);
	pki_base *getSelectedPKI(void *item);
	pki_base *getSelectedPKI(string desc);
	pki_base *getSelectedPKI();
	pki_base *findPKI(pki_base *refpki);
	virtual void loadContainer();
	/* preprocess should be implemented once to speed up updateView() 
	 * i.e search for signers and keys */
	virtual void preprocess() {return;}
	virtual void remFromCont(pki_base *pki);
	virtual void inToCont(pki_base *pki);
	Dbc *getCursor();
	bool freeCursor(Dbc *cursor);
	void *getData(void* key, int length, int *dsize);
	void *getData(string key, int *dsize);
	string getString(string key);
	string getString(char *key);
	int getInt(string key);
	void putData(void *key, int keylen, void *dat, int datalen);
	void putString(string key, void *dat, int datalen);
	void putString(string key, string dat);
	void putString(char *key, string dat);
	void putInt(string key, int dat);
	QPixmap *loadImg(const char *name);
};

#endif