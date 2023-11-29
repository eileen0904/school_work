//
//  Profile.swift
//  Swift_RegistrationForm
//
//  Created by 張芯翎 on 2023/10/24.
//

import Foundation

struct Valid{
    var first = false
    var last = false
    
    var contact_addr = false
    
    var street_addr = false
    var city = false
    var region = false
    var postal = false
    var country = false
    
    var home_tel = false
    var mobile_tel = false
        
    var email = false
}

struct Profile {
    var titleIndex = 0
    var first = ""
    var initials = ""
    var middle = ""
    var last = ""
    
    var genderIndex = 0
    
    var birthday = Date()
    
    var contact_addr = ""
    
    var street_addr = ""
    var street_addr2 = ""
    var city = ""
    var region = ""
    var postal = ""
    var country = ""
    
    var home_tel = ""
    var mobile_tel = ""
        
    var email = ""
}
