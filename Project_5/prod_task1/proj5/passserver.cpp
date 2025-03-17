// *************************
//  Private Member Functions
// *************************

std::string PassServer::encrypt(const std::string & str) {
    char salt[] = "$1$########";
    char *encrypted = crypt(str.c_str(), salt);
    return std::string(encrypted + 12, 22);
}

// ************************
//  Public Member Functions
// ************************

PassServer::PassServer(size_t size) {
    adaptedTable = new HashTable<std::string, std::string>(size);
}
   
PassServer::~PassServer() {
    delete adaptedTable;
    adaptedTable = nullptr;
}

bool PassServer::load(const char *filename) {
    std::ifstream infile(filename);
    if (!infile) {
        return false;
    }
    std::string key;
    std::string value;
    while (infile >> key >> value) {
        addUser({ key, encrypt(value) });
    }
    return true;
}

bool PassServer::addUser(std::pair<std::string, std::string> & kv) {
    if(adaptedTable->contains(kv.first)) {
        return false;
    }

    std::string encryptedPass = encrypt(kv.second);
    std::pair<std::string, std::string> newPair(kv.first, encryptedPass);

    return adaptedTable->insert(newPair);
}

bool PassServer::addUser(std::pair<std::string, std::string> && kv) {
    if(adaptedTable->contains(std::move(kv.first))) {
        return false;
    }
    std::string encryptedPass = encrypt(kv.second);
    std::pair<std::string, std::string> newPair(std::move(kv.first), encryptedPass);
    
    return adaptedTable->insert(newPair);
}

bool PassServer::removeUser(const std::string & k) {
    return adaptedTable->remove(k);
}

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword) {
    std::string userName = p.first;
    std::string oldPassword = encrypt(p.second);
    std::string newPassword = encrypt(newpassword);

    if (adaptedTable->remove(userName)) { 
        std::pair<std::string, std::string> newPair(userName, newPassword);
        return adaptedTable->insert(newPair);
        return true;
    }
    return false;
}

bool PassServer::find(const std::string & user) const {
    return adaptedTable->contains(user);
}

void PassServer::dump() {
    adaptedTable->dump();
}

size_t PassServer::size() const {
    return adaptedTable->size();
}

bool PassServer::write_to_file(const char *filename) const {
    return adaptedTable->write_to_file(filename);
}