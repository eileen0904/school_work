//
//  Item.swift
//  Swift_Conuter_Control
//
//  Created by 張芯翎 on 2023/10/18.
//

import Foundation
import SwiftData

class CounterViewModel: ObservableObject {
    
    @Published var counter: Int = 0
    
    func increaseCounter() {
        counter += 1
    }
}
