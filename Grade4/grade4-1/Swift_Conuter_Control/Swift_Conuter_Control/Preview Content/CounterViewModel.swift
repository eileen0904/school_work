//
//  CounterViewModel.swift
//  Swift_Conuter_Control
//
//  Created by 張芯翎 on 2023/10/18.
//

import Foundation

class CounterViewModel: ObservableObject {
    @Published var counter: Int = 0

    func increase() {
        counter += 1
    }

    func decrease() {
        counter -= 1
    }

    func reset() {
        counter = 0
    }
}

