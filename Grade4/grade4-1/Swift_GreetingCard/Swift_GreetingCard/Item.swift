//
//  Item.swift
//  Swift_GreetingCard
//
//  Created by 張芯翎 on 2023/10/11.
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
