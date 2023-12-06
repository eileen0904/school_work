//
//  Restaurants.swift
//  Swift_DataFiltering
//
//  Created by 張芯翎 on 2023/11/24.
//

import Foundation

struct Restaurant: Identifiable {
    var id = UUID()
    var name: String = ""
    var type: String = ""
    var location: String = ""
    var image: String = ""
}
