//
//  Item.swift
//  Swift_TempConvert
//
//  Created by 張芯翎 on 2023/10/18.
//

import Foundation
import SwiftData

@Model
final class Item {
    var timestamp: Date
    
    init(timestamp: Date) {
        self.timestamp = timestamp
    }
}
